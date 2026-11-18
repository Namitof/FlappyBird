#include "scenes/gameplay.h"

#include "raylib.h"

#include "background/background.h"
#include "entities/player.h"
#include "entities/obstacle.h"
#include "ui/text.h"
#include "resources/audio_manager.h"
#include "resources/resource_manager.h"

namespace ReyesCuadra
{
	// Estados posibles dentro de una partida
	enum class RunState
	{
		Playing,
		GameOver
	};

	// Motivos por los que se puede perder
	enum class DefeatReason
	{
		ObstacleCollision,
		FellToFloor,
		AllPlayersEliminated
	};

	// Teclas de esta escena
	static const KeyboardKey BACK_TO_MENU_KEY = KEY_ESCAPE;
	static const KeyboardKey RESTART_KEY = KEY_R;

	// Textos que ve el usuario
	static const char* CONTROLS_TEXT = "Pasa por el hueco del obstaculo verde";
	static const char* BACK_TO_MENU_TEXT = "ESC para volver al menu";
	static const char* GAME_OVER_TITLE_TEXT = "PERDISTE";
	static const char* OBSTACLE_DEFEAT_TEXT = "Chocaste contra el obstaculo";
	static const char* FLOOR_DEFEAT_TEXT = "Caiste al piso";
	static const char* PLAYERS_DEFEAT_TEXT = "Todos los jugadores fueron eliminados";
	static const char* GAME_OVER_OPTIONS_TEXT = "Presiona R para reiniciar o ESC para volver al menu";

	// Distribucion de los textos
	static const int TEXT_MARGIN = 10;
	static const int SMALL_FONT_SIZE = 20;
	static const int TITLE_FONT_SIZE = 60;
	static const int GAME_OVER_LINE_SPACING = 50;
	static const float DEFAULT_SPACING = 1.0f;

	// Colores
	static const Color GAMEPLAY_BACKGROUND_COLOR = SKYBLUE;
	static const Color TEXT_COLOR = DARKGRAY;
	static const Color GAME_OVER_TITLE_COLOR = RED;

	// Todo lo que la partida necesita mientras se juega
	struct GameplayState
	{
		Background background;
		Player playerOne;
		Player playerTwo;
		Obstacle obstacle;
		RunState runState;
		DefeatReason defeatReason;
		bool isMultiplayerModeActive;
		bool playerOneDefeat;
		bool playerTwoDefeat;
	};

	// Controles de cada jugador
	const KeyboardKey JUMP_PLAYER_ONE = KEY_SPACE;
	const KeyboardKey JUMP_PLAYER_TWO = KEY_UP;

	// Colores de cada jugador
	const Color COLOR_PLAYER_ONE = YELLOW;
	const Color COLOR_PLAYER_TWO = PINK;

	// Punto de aparicion en eje x de cada jugador
	static const float PLAYER_TWO_POSITION_X = 100.0f;
	static const float PLAYER_ONE_POSITION_X = 150.0f;

	// Estado de la partida actual (solo se usa en este archivo)
	static GameplayState gameplay;

	// Fuente
	Font gameFont;

	// Mueve el fondo, al jugador y al obstaculo y chequea las condiciones de derrota
	static void UpdatePlaying(float deltaTime);

	// Termina la partida guardando el motivo, para mostrarlo en el mensaje de derrota
	static void EndRun(DefeatReason reason);

	// Espera a que el usuario elija reiniciar despues de perder
	static void UpdateGameOver();

	// Dibuja los controles en la parte de arriba de la pantalla
	static void DrawHud();

	// Dibuja el mensaje de derrota, su motivo y las opciones disponibles
	static void DrawGameOverMessage(DefeatReason reason);

	// Devuelve el texto que explica el motivo de la derrota
	static const char* GetDefeatReasonText(DefeatReason reason);

	void InitGameplay(bool isMultiplayerModeActive)
	{
		const int screenWidth = GetScreenWidth();
		const int screenHeight = GetScreenHeight();

		gameFont = GetFont();

		gameplay.background = CreateBackground(screenWidth);
		gameplay.playerOne = CreatePlayer(screenHeight, JUMP_PLAYER_ONE, COLOR_PLAYER_ONE, PLAYER_ONE_POSITION_X, PLAYER_ONE_ID);
		gameplay.playerTwo = CreatePlayer(screenHeight, JUMP_PLAYER_TWO, COLOR_PLAYER_TWO, PLAYER_TWO_POSITION_X, PLAYER_TWO_ID);
		gameplay.obstacle = CreateObstacle(screenWidth, screenHeight);
		gameplay.runState = RunState::Playing;
		gameplay.defeatReason = DefeatReason::ObstacleCollision;
		gameplay.isMultiplayerModeActive = isMultiplayerModeActive;
		gameplay.playerOneDefeat = false;
		gameplay.playerTwoDefeat = false;
	}

	Scene UpdateGameplay()
	{
		// Se puede volver al menu en cualquier momento, tanto jugando como despues de perder
		if (IsKeyPressed(BACK_TO_MENU_KEY))
		{
			return Scene::MainMenu;
		}

		switch (gameplay.runState)
		{
		case RunState::Playing:
			UpdatePlaying(GetFrameTime());
			break;

		case RunState::GameOver:
			UpdateGameOver();
			break;
		}

		return Scene::Gameplay;
	}

	void DrawGameplay()
	{
		ClearBackground(GAMEPLAY_BACKGROUND_COLOR);

		// El fondo va primero para que todo lo demas se dibuje encima
		DrawBackground(gameplay.background, GetScreenHeight());

		// Los elementos se siguen dibujando despues de perder, para que el jugador vea como fue el choque
		DrawObstacle(gameplay.obstacle);
		if (gameplay.playerOne.isActive)
		{
			DrawPlayer(gameplay.playerOne);

		}
		if (gameplay.isMultiplayerModeActive && gameplay.playerTwo.isActive)
		{
			DrawPlayer(gameplay.playerTwo);
		}

		DrawHud();

		if (gameplay.runState == RunState::GameOver)
		{
			DrawGameOverMessage(gameplay.defeatReason);
		}
	}

	static void UpdatePlaying(float deltaTime)
	{
		PlayGameMusic();

		// El fondo solo se mueve mientras se juega, igual que el obstaculo
		UpdateBackground(gameplay.background, deltaTime);
		if (gameplay.playerOne.isActive)
		{
			UpdatePlayer(gameplay.playerOne, deltaTime);
		}
		if (gameplay.isMultiplayerModeActive && gameplay.playerTwo.isActive)
		{
			UpdatePlayer(gameplay.playerTwo, deltaTime);
		}
		UpdateObstacle(gameplay.obstacle, GetScreenWidth(), GetScreenHeight(), deltaTime);

		// Condiciones de derrota: el jugador toca el obstaculo o cae hasta el piso
		if (IsCollidingWithObstacle(gameplay.obstacle, gameplay.playerOne.body))
		{
			if (!gameplay.playerOneDefeat)
			{
				PlayHitPipeSound();
				gameplay.playerOneDefeat = true;
			}

			if (!gameplay.isMultiplayerModeActive)
			{
				EndRun(DefeatReason::ObstacleCollision);
			}
			else
			{
				gameplay.playerOne.isActive = false;
			}
		}
		else if (HasPlayerReachedFloor(gameplay.playerOne, GetScreenHeight()))
		{
			if (!gameplay.playerOneDefeat)
			{
				PlayHitFloorSound();
				gameplay.playerOneDefeat = true;
			}

			if (!gameplay.isMultiplayerModeActive)
			{
				EndRun(DefeatReason::FellToFloor);
			}
			else
			{
				gameplay.playerOne.isActive = false;
			}
		}

		if (gameplay.isMultiplayerModeActive)
		{
			if (IsCollidingWithObstacle(gameplay.obstacle, gameplay.playerTwo.body))
			{
				if (!gameplay.playerTwoDefeat)
				{
					PlayHitPipeSound();
					gameplay.playerTwoDefeat = true;
				}
				gameplay.playerTwo.isActive = false;
			}
			else if (HasPlayerReachedFloor(gameplay.playerTwo, GetScreenHeight()))
			{
				if (!gameplay.playerTwoDefeat)
				{
					PlayHitFloorSound();
					gameplay.playerTwoDefeat = true;
				}
				gameplay.playerTwo.isActive = false;
			}

			if (!gameplay.playerOne.isActive && !gameplay.playerTwo.isActive)
			{
				PlayGameOverSound();
				EndRun(DefeatReason::AllPlayersEliminated);
			}

		}
	}

	static void EndRun(DefeatReason reason)
	{
		if (gameplay.playerTwoDefeat || gameplay.playerOneDefeat)
		{
			PlayGameOverSound();
		}
		gameplay.runState = RunState::GameOver;
		gameplay.defeatReason = reason;
	}

	static void UpdateGameOver()
	{
		StopGameMusic();

		// Reiniciar arranca otra partida sin tener que pasar por el menu
		if (IsKeyPressed(RESTART_KEY))
		{
			InitGameplay(gameplay.isMultiplayerModeActive);
		}
	}

	static void DrawHud()
	{
		Vector2 pos = { static_cast<float>(TEXT_MARGIN), static_cast<float>(TEXT_MARGIN) };
		DrawTextEx(gameFont, CONTROLS_TEXT, pos, SMALL_FONT_SIZE, DEFAULT_SPACING, TEXT_COLOR);
		pos = { static_cast<float>(TEXT_MARGIN), static_cast<float>(TEXT_MARGIN * 3) };
		DrawTextEx(gameFont, BACK_TO_MENU_TEXT, pos, SMALL_FONT_SIZE, DEFAULT_SPACING, TEXT_COLOR);
	}

	static void DrawGameOverMessage(DefeatReason reason)
	{
		const int titlePositionY = GetScreenHeight() / 2 - TITLE_FONT_SIZE;
		const int reasonPositionY = titlePositionY + TITLE_FONT_SIZE + TEXT_MARGIN;
		const int optionsPositionY = reasonPositionY + GAME_OVER_LINE_SPACING;

		DrawCenteredText(GAME_OVER_TITLE_TEXT, titlePositionY, TITLE_FONT_SIZE, GAME_OVER_TITLE_COLOR, gameFont, DEFAULT_SPACING);
		DrawCenteredText(GetDefeatReasonText(reason), reasonPositionY, SMALL_FONT_SIZE, TEXT_COLOR, gameFont, DEFAULT_SPACING);
		DrawCenteredText(GAME_OVER_OPTIONS_TEXT, optionsPositionY, SMALL_FONT_SIZE, TEXT_COLOR, gameFont, DEFAULT_SPACING);
	}

	static const char* GetDefeatReasonText(DefeatReason reason)
	{
		if (reason == DefeatReason::ObstacleCollision)
		{
			return OBSTACLE_DEFEAT_TEXT;
		}
		else if (reason == DefeatReason::FellToFloor)
		{
			return FLOOR_DEFEAT_TEXT;
		}
		else
		{
			return PLAYERS_DEFEAT_TEXT;
		}
	}
}