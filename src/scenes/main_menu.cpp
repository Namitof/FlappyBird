#include "scenes/main_menu.h"

#include <iterator>

#include "raylib.h"

#include "ui/button.h"
#include "ui/text.h"
#include "resources/audio_manager.h"
#include "resources/resource_manager.h"

namespace ReyesCuadra
{
    // Textos que ve el usuario
    static const char* GAME_TITLE_TEXT = "FLAPPY GEOMETRY";
    static const char* MENU_HINT_TEXT = "Hace clic en una opcion";
    static const char* PLAY_BUTTON_TEXT = "Jugar";
    static const char* GAME_MODE_BUTTON_TEXT = "1 Jugador";
    static const char* CREDITS_BUTTON_TEXT = "Creditos";
    static const char* EXIT_BUTTON_TEXT = "Salir";
    static const char* CONTROLS_TITLE_TEXT = "Controles:";
    static const char* SOUNDS_TITLE_TEXT = "Sonidos:";
    static const char* BUTTON_SOUNDS_STATE_TEXT = "Activados";

    // Version del juego, que ahora se muestra en un borde del menu
    static const char* GAME_VERSION_TEXT = "v1.0";

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
    static const float SOUNDS_BUTTON_SPAWN_X = 80.0f;
    static const int SOUNDS_BUTTON_TEXT_SPAWN_X = 150;
    static const int SOUNDS_BUTTON_TEXT_OFFSET_Y = 20;
    static const float DEFAULT_SPACING = 0.0f;

    // Colores
    static const Color MENU_BACKGROUND_COLOR = SKYBLUE;
    static const Color TITLE_COLOR = RED;
    static const Color TEXT_COLOR = BLACK;
    static const Color CONTROLS_TITLE_COLOR = DARKBLUE;

    // Botones del menu (solo se usan en este archivo)
    static Button playButton;
    static Button gameModeButton;
    static Button creditsButton;
    static Button instructionsButton;
    static Button exitButton;
    static Button soundsButton;

    // Booleano para controlar si los sonidos estan activos
    static bool soundsActives;
    
    // Booleano para controlar modo de juego
    static bool isMultiplayerModeActive;

    // Fuente
    static Font menuFont;

    // Background
    static Texture2D menuBackground;

    // Dibuja la version del juego en la esquina inferior derecha
    static void DrawGameVersion();

    void InitMainMenu()
    {
        menuFont = GetFont();

        // Los botones van uno debajo del otro, centrados en la pantalla
        menuBackground = GetMenuBackground();
        playButton = CreateCenteredButton(PLAY_BUTTON_TEXT, FIRST_BUTTON_POSITION_Y, menuFont);
        gameModeButton = CreateCenteredButton(GAME_MODE_BUTTON_TEXT, FIRST_BUTTON_POSITION_Y + BUTTON_SPACING, menuFont);
        creditsButton = CreateCenteredButton(CREDITS_BUTTON_TEXT, FIRST_BUTTON_POSITION_Y + BUTTON_SPACING * 2.0f, menuFont);
        exitButton = CreateCenteredButton(EXIT_BUTTON_TEXT, FIRST_BUTTON_POSITION_Y + BUTTON_SPACING * 3.0f, menuFont);

        soundsButton = CreateButton(BUTTON_SOUNDS_STATE_TEXT, SOUNDS_BUTTON_SPAWN_X, FIRST_BUTTON_POSITION_Y + BUTTON_SPACING, menuFont);
        soundsActives = true;
    }

    Scene UpdateMainMenu(bool& multiplayerMode)
    {
        PlayMenuMusic();

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

        if (IsButtonClicked(soundsButton))
        {
            soundsActives = !soundsActives;
        }

        if (soundsActives)
        {
            soundsButton.text = "Activados";
            SoundsTurnOn();
        }
        else
        {
            soundsButton.text = "Desactivados";
            SoundsTurnOff();
        }

        if (IsButtonClicked(playButton))
        {
            multiplayerMode = isMultiplayerModeActive;
            StopMenuMusic();
            return Scene::Rules;
        }

        if (IsButtonClicked(creditsButton))
        {
            return Scene::Credits;
        }

        if (IsButtonClicked(exitButton))
        {
            StopMenuMusic();
            return Scene::Exit;
        }

        // Si no se eligio nada, se sigue en el menu
        return Scene::MainMenu;
    }

    void DrawMainMenu()
    {
        ClearBackground(MENU_BACKGROUND_COLOR);

        DrawTexture(menuBackground, 0, 0, WHITE);

        DrawCenteredText(GAME_TITLE_TEXT, TITLE_POSITION_Y, TITLE_FONT_SIZE, TITLE_COLOR, menuFont, DEFAULT_SPACING);
        DrawCenteredText(MENU_HINT_TEXT, HINT_POSITION_Y, SMALL_FONT_SIZE, TEXT_COLOR, menuFont, DEFAULT_SPACING);

        DrawButton(playButton);
        DrawButton(gameModeButton);
        DrawButton(creditsButton);
        DrawButton(exitButton);

        DrawButton(soundsButton);
        DrawTextEx(menuFont, SOUNDS_TITLE_TEXT, { SOUNDS_BUTTON_TEXT_SPAWN_X, FIRST_BUTTON_POSITION_Y + BUTTON_SPACING - SOUNDS_BUTTON_TEXT_OFFSET_Y }, SMALL_FONT_SIZE, DEFAULT_SPACING, TEXT_COLOR);

        DrawGameVersion();
    }

    static void DrawGameVersion()
    {
        const int versionTextWidth = MeasureText(GAME_VERSION_TEXT, SMALL_FONT_SIZE);
        const int versionPositionX = GetScreenWidth() - versionTextWidth - TEXT_MARGIN;
        const int versionPositionY = GetScreenHeight() - SMALL_FONT_SIZE - TEXT_MARGIN;

        Vector2 pos = { static_cast<float>(versionPositionX), static_cast<float>(versionPositionY) };

        DrawTextEx(menuFont, GAME_VERSION_TEXT, pos, SMALL_FONT_SIZE, DEFAULT_SPACING, TEXT_COLOR);
    }
}