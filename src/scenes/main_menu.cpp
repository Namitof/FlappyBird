#include "scenes/main_menu.h"
#include <iterator>
#include "raylib.h"

#include "ui/button.h"
#include "ui/text.h"

namespace ReyesCuadra
{
    // Textos que ve el usuario
    static const char* GAME_TITLE_TEXT = "FLAPPY BIRD";
    static const char* MENU_HINT_TEXT = "Hace clic en una opcion";
    static const char* PLAY_BUTTON_TEXT = "Jugar";
    static const char* GAME_MODE_BUTTON_TEXT = "1 Jugador";
    static const char* CREDITS_BUTTON_TEXT = "Creditos";
    static const char* EXIT_BUTTON_TEXT = "Salir";
    static const char* CONTROLS_TITLE_TEXT = "Controles:";

    static const char* CONTROLS_LINES[] =
    {
        "P1 Color -> Amarillo",
        "P2 Color -> Rosa",
        "P1 Saltar -> Espacio",
        "P2 Saltar -> Flecha arriba",
        "R para reiniciar",
        "Escape para salir"
    };

    // Version del juego, que ahora se muestra en un borde del menu
    static const char* GAME_VERSION_TEXT = "v0.4";

    // Distribucion de los elementos en la pantalla
    static const int TITLE_POSITION_Y = 40;
    static const int TITLE_FONT_SIZE = 60;
    static const int HINT_POSITION_Y = 100;
    static const int SMALL_FONT_SIZE = 20;
    static const int TEXT_MARGIN = 10;
    static const float FIRST_BUTTON_POSITION_Y = 150.0f;
    static const float BUTTON_SPACING = 70.0f; // Distancia vertical entre el comienzo de un boton y el siguiente
    static const int CONTROLS_POSITION_X = 20;
    static const int CONTROLS_TITLE_POSITION_Y = 130;
    static const int CONTROLS_FIRST_LINE_POSITION_Y = 180;
    static const int CONTROLS_LINE_SPACING = 30;

    // Colores
    static const Color MENU_BACKGROUND_COLOR = SKYBLUE;
    static const Color TITLE_COLOR = DARKGREEN;
    static const Color TEXT_COLOR = DARKGRAY;
    static const Color CONTROLS_TITLE_COLOR = DARKBLUE;

    // Botones del menu (solo se usan en este archivo)
    static Button playButton;
    static Button gameModeButton;
    static Button creditsButton;
    static Button instructionsButton;
    static Button exitButton;

    // Booleano para controlar modo de juego
    static bool isMultiplayerModeActive;

    // Dibuja la version del juego en la esquina inferior derecha
    static void DrawGameVersion();
    static void DrawGameInstructions();

    void InitMainMenu()
    {
        // Los botones van uno debajo del otro, centrados en la pantalla
        playButton = CreateCenteredButton(PLAY_BUTTON_TEXT, FIRST_BUTTON_POSITION_Y);
        gameModeButton = CreateCenteredButton(GAME_MODE_BUTTON_TEXT, FIRST_BUTTON_POSITION_Y + BUTTON_SPACING );
        creditsButton = CreateCenteredButton(CREDITS_BUTTON_TEXT, FIRST_BUTTON_POSITION_Y + BUTTON_SPACING * 2.0f);
        exitButton = CreateCenteredButton(EXIT_BUTTON_TEXT, FIRST_BUTTON_POSITION_Y + BUTTON_SPACING * 3.0f);
    }

    Scene UpdateMainMenu(bool& multiplayerMode)
    {
        if (IsButtonClicked(gameModeButton))
        {
            isMultiplayerModeActive = !isMultiplayerModeActive;
        }

        if (isMultiplayerModeActive)
        {
            gameModeButton.text = "2 Jugadores";
        }
        else
        {
            gameModeButton.text = "1 Jugador";
        }

        if (IsButtonClicked(playButton))
        {
            multiplayerMode = isMultiplayerModeActive;
            return Scene::Gameplay;
        }

        if (IsButtonClicked(creditsButton))
        {
            return Scene::Credits;
        }

        if (IsButtonClicked(exitButton))
        {
            return Scene::Exit;
        }

        // Si no se eligio nada, se sigue en el menu
        return Scene::MainMenu;
    }

    void DrawMainMenu()
    {
        ClearBackground(MENU_BACKGROUND_COLOR);

        DrawCenteredText(GAME_TITLE_TEXT, TITLE_POSITION_Y, TITLE_FONT_SIZE, TITLE_COLOR);
        DrawCenteredText(MENU_HINT_TEXT, HINT_POSITION_Y, SMALL_FONT_SIZE, TEXT_COLOR);

        DrawButton(playButton);
        DrawButton(gameModeButton);
        DrawButton(creditsButton);
        DrawButton(exitButton);

        DrawGameInstructions();

        DrawGameVersion();
    }

    static void DrawGameVersion()
    {
        const int versionTextWidth = MeasureText(GAME_VERSION_TEXT, SMALL_FONT_SIZE);
        const int versionPositionX = GetScreenWidth() - versionTextWidth - TEXT_MARGIN;
        const int versionPositionY = GetScreenHeight() - SMALL_FONT_SIZE - TEXT_MARGIN;

        DrawText(GAME_VERSION_TEXT, versionPositionX, versionPositionY, SMALL_FONT_SIZE, TEXT_COLOR);
    }

    static void DrawGameInstructions()
    {
        DrawText(CONTROLS_TITLE_TEXT, CONTROLS_POSITION_X, CONTROLS_TITLE_POSITION_Y, SMALL_FONT_SIZE, CONTROLS_TITLE_COLOR);

        const int lineCount = static_cast<int>(std::size(CONTROLS_LINES));

        for (int lineIndex = 0; lineIndex < lineCount; lineIndex++)
        {
            const int linePositionY = CONTROLS_FIRST_LINE_POSITION_Y + lineIndex * CONTROLS_LINE_SPACING;

            DrawText(CONTROLS_LINES[lineIndex], CONTROLS_POSITION_X, linePositionY, SMALL_FONT_SIZE, CONTROLS_TITLE_COLOR);
        }
    }
}
