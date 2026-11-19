#include "ui/button.h"

#include "raylib.h"

#include "resources/audio_manager.h"

namespace ReyesCuadra
{
    // Tamano y estilo de los botones (solo se usan en este archivo)
    static const float BUTTON_WIDTH = 200.0f;
    static const float BUTTON_HEIGHT = 50.0f;
    static const float BUTTON_BORDER_THICKNESS = 3.0f;
    static const int BUTTON_FONT_SIZE = 25;
    static const float DEFAULT_SPACING = 1.0f;

    static const Color BUTTON_COLOR = LIGHTGRAY;
    static const Color BUTTON_HOVER_COLOR = YELLOW;
    static const Color BUTTON_BORDER_COLOR = DARKGRAY;
    static const Color BUTTON_TEXT_COLOR = DARKGRAY;

    Button CreateCenteredButton(const char* text, float positionY, Font font)
    {
        Button button;

        button.bounds.width = BUTTON_WIDTH;
        button.bounds.height = BUTTON_HEIGHT;
        button.bounds.x = (static_cast<float>(GetScreenWidth()) - BUTTON_WIDTH) / 2.0f;
        button.bounds.y = positionY;
        button.text = text;
        button.isHovered = false;
        button.soundsPlaying = false;
        button.font = font;

        return button;
    }

    Button CreateButton(const char* text, float positionX, float positionY, Font font)
    {
        Button button;

        button.bounds.width = BUTTON_WIDTH;
        button.bounds.height = BUTTON_HEIGHT;
        button.bounds.x = positionX;
        button.bounds.y = positionY;
        button.text = text;
        button.isHovered = false;
        button.soundsPlaying = false;
        button.font = font;

        return button;
    }

    bool IsButtonHovered(Button& button)
    {
        button.isHovered = CheckCollisionPointRec(GetMousePosition(), button.bounds);
        if (button.isHovered && !button.soundsPlaying)
        {
            PlaySelectSound();
            button.soundsPlaying = true;
        }
        return button.isHovered;
    }

    bool IsButtonClicked(Button& button)
    {
        button.soundsPlaying = button.isHovered;
        return IsButtonHovered(button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    }

    void DrawButton(Button& button)
    {
        // Se resalta el boton cuando el mouse esta encima, para que el usuario sepa que se puede apretar
        const Color fillColor = IsButtonHovered(button) ? BUTTON_HOVER_COLOR : BUTTON_COLOR;

        DrawRectangleRec(button.bounds, fillColor);
        DrawRectangleLinesEx(button.bounds, BUTTON_BORDER_THICKNESS, BUTTON_BORDER_COLOR);

        // El texto va centrado dentro del boton
        //const int textWidth = MeasureText(button.text, BUTTON_FONT_SIZE);

        const Vector2 measureText = MeasureTextEx(button.font, button.text, static_cast<float>(BUTTON_FONT_SIZE), DEFAULT_SPACING);
        const int textWidth = static_cast<int>(measureText.x);

        const int textPositionX = static_cast<int>(button.bounds.x + (button.bounds.width - static_cast<float>(textWidth)) / 2.0f);
        const int textPositionY = static_cast<int>(button.bounds.y + (button.bounds.height - static_cast<float>(BUTTON_FONT_SIZE)) / 2.0f);

        Vector2 pos = { static_cast<float>(textPositionX), static_cast<float>(textPositionY) };

        DrawTextEx(button.font, button.text, pos, static_cast<float>(BUTTON_FONT_SIZE), DEFAULT_SPACING, BUTTON_TEXT_COLOR);

        //DrawText(button.text, textPositionX, textPositionY, BUTTON_FONT_SIZE, BUTTON_TEXT_COLOR);
    }
}