#include "scenes/credits.h"

#include <iterator>

#include "raylib.h"

#include "ui/button.h"
#include "ui/text.h"

namespace ReyesCuadra
{
    // Una linea de texto de los creditos: los titulos de seccion se dibujan destacados
    struct CreditLine
    {
        const char* text;
        bool isSectionTitle;
    };

    // Tecla para volver al menu (la misma que en el gameplay)
    static const KeyboardKey BACK_TO_MENU_KEY = KEY_ESCAPE;

    // Textos que ve el usuario
    static const char* CREDITS_TITLE_TEXT = "CREDITOS";
    static const char* BACK_BUTTON_TEXT = "Volver";
    static const char* BACK_TO_MENU_TEXT = "Tambien podes volver con ESC";

    // Contenido de los creditos, en el orden en que se muestran
    static const CreditLine CREDIT_LINES[] =
    {
        { "Desarrollo y programacion", true },
        { "Valentin Reyes Cuadra", false },
        { "Nahuel Suarez", false },
        { "Herramientas", true },
        { "raylib 6.2 (https://www.raylib.com)", false },
        { "Visual Studio 2026", false },
    };

    // Distribucion de los elementos en la pantalla
    static const int TITLE_POSITION_Y = 30;
    static const int TITLE_FONT_SIZE = 50;
    static const int FIRST_LINE_POSITION_Y = 100;
    static const int LINE_FONT_SIZE = 20;
    static const int LINE_SPACING = 27;           // Distancia vertical entre una linea y la siguiente
    static const int SECTION_EXTRA_SPACING = 15;  // Espacio extra antes de cada titulo de seccion, para separarlas
    static const int BOTTOM_MARGIN = 30;
    static const float BACK_BUTTON_POSITION_Y = 320.0f; // Debajo de las lineas de los creditos

    // Colores
    static const Color CREDITS_BACKGROUND_COLOR = SKYBLUE;
    static const Color TITLE_COLOR = DARKGREEN;
    static const Color SECTION_TITLE_COLOR = DARKBLUE;
    static const Color TEXT_COLOR = DARKGRAY;

    // Boton para volver al menu, igual a los del menu principal (solo se usa en este archivo)
    static Button backButton;

    // Dibuja todas las lineas de los creditos, una debajo de la otra
    static void DrawCreditLines();

    void InitCredits()
    {
        backButton = CreateCenteredButton(BACK_BUTTON_TEXT, BACK_BUTTON_POSITION_Y);
    }

    Scene UpdateCredits()
    {
        // Se vuelve al menu con el boton, igual que se navega en el menu, o con ESC, igual que en el gameplay
        if (IsButtonClicked(backButton) || IsKeyPressed(BACK_TO_MENU_KEY))
        {
            return Scene::MainMenu;
        }

        return Scene::Credits;
    }

    void DrawCredits()
    {
        ClearBackground(CREDITS_BACKGROUND_COLOR);

        DrawCenteredText(CREDITS_TITLE_TEXT, TITLE_POSITION_Y, TITLE_FONT_SIZE, TITLE_COLOR);

        DrawCreditLines();

        DrawButton(backButton);

        // Abajo de todo se recuerda que tambien se puede volver con el teclado
        const int backTextPositionY = GetScreenHeight() - BOTTOM_MARGIN;

        DrawCenteredText(BACK_TO_MENU_TEXT, backTextPositionY, LINE_FONT_SIZE, TEXT_COLOR);
    }

    static void DrawCreditLines()
    {
        int positionY = FIRST_LINE_POSITION_Y;

        for (int lineIndex = 0; lineIndex < static_cast<int>(std::size(CREDIT_LINES)); lineIndex++)
        {
            const CreditLine& line = CREDIT_LINES[lineIndex];

            // Antes de cada titulo de seccion (menos el primero) se deja un espacio extra
            if (line.isSectionTitle && lineIndex > 0)
            {
                positionY += SECTION_EXTRA_SPACING;
            }

            const Color lineColor = line.isSectionTitle ? SECTION_TITLE_COLOR : TEXT_COLOR;

            DrawCenteredText(line.text, positionY, LINE_FONT_SIZE, lineColor);

            positionY += LINE_SPACING;
        }
    }
}