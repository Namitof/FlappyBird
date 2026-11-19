#include "scenes/instructions.h"

#include <iterator>

#include "raylib.h"

#include "ui/text.h"
#include "scenes/scene.h"
#include "resources/resource_manager.h"

namespace ReyesCuadra
{
    // Una linea de texto de los creditos: los titulos de seccion se dibujan destacados
    struct InstructionLine
    {
        const char* text;
        bool isSectionTitle;
        Color color;
        bool isActive;
    };

    // Tecla para volver al menu (la misma que en el gameplay)
    static const KeyboardKey BACK_TO_MENU_KEY = KEY_ESCAPE;

    // Textos que ve el usuario
    static const char* RULES_TITLE_TEXT = "REGLAS";
    static const char* PLAY_TEXT = "ESC para volver al menu";

    // Distribucion de los elementos en la pantalla
    static const int TITLE_POSITION_Y = 30;
    static const int TITLE_FONT_SIZE = 50;
    static const int FIRST_LINE_POSITION_Y = 100;
    static const int LINE_FONT_SIZE = 20;
    static const int LINE_SPACING = 27;           // Distancia vertical entre una linea y la siguiente
    static const int SECTION_EXTRA_SPACING = 15;  // Espacio extra antes de cada titulo de seccion, para separarlas
    static const int BOTTOM_MARGIN = 30;
    static const float DEFAULT_SPACING = 1.0f;

    // Colores
    static const Color RULES_BACKGROUND_COLOR = SKYBLUE;
    static const Color TITLE_COLOR = RED;
    static const Color SECTION_TITLE_COLOR = DARKBLUE;

    static const Color TEXT_COLOR = BLACK;

    static const Color PLAYER_ONE_COLOR = YELLOW;
    static const Color PLAYER_TWO_COLOR = PINK;

    // Contenido de las reglas, en el orden en que se muestran
    static InstructionLine RULES_LINES[] =
    {
        { " Pasa por el hueco del obstaculo verde", false, TEXT_COLOR },
        { " = JUGADOR 1 (Amarillo) = ", true, PLAYER_ONE_COLOR },
        { " - Espacio para saltar - ", false, TEXT_COLOR },
        { " = JUGADOR 2 (Rosa) = ", true, PLAYER_TWO_COLOR },
        { " - Flecha arriba para saltar - ", false, TEXT_COLOR },
        { " = GENERAL = ", true, SECTION_TITLE_COLOR },
        { " - R para reiniciar - ", false, TEXT_COLOR},
        { " - Escape para salir - ", false, TEXT_COLOR },
    };

    // Fuente
    static Font rulesFont;

    // Background
    static Texture2D creditsBackground;

    // Dibuja todas las lineas de los creditos, una debajo de la otra
    static void DrawRulesLines();

    void InitRules(bool isMultiplayerModeActive)
    {
        rulesFont = GetFont();
        creditsBackground = GetMenuBackground();
        for (int lineIndex = 0; lineIndex < static_cast<int>(std::size(RULES_LINES)); lineIndex++)
        {
            if (!isMultiplayerModeActive && ((lineIndex == 3) || (lineIndex == 4)))
            {
                RULES_LINES[lineIndex].isActive = false;
            }
            else
            {
                RULES_LINES[lineIndex].isActive = true;
            }
        }
    }

    Scene UpdateRules()
    {
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP))
        {
            return Scene::Gameplay;
        }
        else if (IsKeyPressed(BACK_TO_MENU_KEY))
        {
            return Scene::MainMenu;
        }

        return Scene::Rules;
    }

    void DrawRules()
    {
        ClearBackground(RULES_BACKGROUND_COLOR);

        DrawTexture(creditsBackground, 0, 0, WHITE);

        DrawCenteredText(RULES_TITLE_TEXT, TITLE_POSITION_Y, TITLE_FONT_SIZE, TITLE_COLOR, rulesFont, DEFAULT_SPACING);

        DrawRulesLines();

        // La indicacion para volver va abajo de todo, para que el usuario sepa como salir de la pantalla
        const int backTextPositionY = GetScreenHeight() - BOTTOM_MARGIN;

        DrawCenteredText(PLAY_TEXT, backTextPositionY, LINE_FONT_SIZE, TEXT_COLOR, rulesFont, DEFAULT_SPACING);
    }

    static void DrawRulesLines()
    {
        int positionY = FIRST_LINE_POSITION_Y;

        for (int lineIndex = 0; lineIndex < static_cast<int>(std::size(RULES_LINES)); lineIndex++)
        {
            const InstructionLine& line = RULES_LINES[lineIndex];

            // Antes de cada titulo de seccion (menos el primero) se deja un espacio extra
            if (line.isSectionTitle && lineIndex > 0)
            {
                positionY += SECTION_EXTRA_SPACING;
            }
            if (line.isActive)
            {
                DrawCenteredText(line.text, positionY, LINE_FONT_SIZE, line.color, rulesFont, DEFAULT_SPACING);
                positionY += LINE_SPACING;
            }
        }
    }
}
