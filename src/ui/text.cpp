#include "ui/text.h"

#include "raylib.h"

#include "resources/resource_manager.h"

namespace ReyesCuadra
{
    void DrawCenteredText(const char* text, int positionY, int fontSize, Color color, Font font, float spacing)
    {
        // Se usa el ancho real de la ventana, asi sirve para cualquier escena
        const Vector2 measureText = MeasureTextEx(font, text, static_cast<float>(fontSize), spacing);
        const int positionX = static_cast<int>((GetScreenWidth() - measureText.x) / 2.0f);

        Vector2 pos = { static_cast<float>(positionX), static_cast<float>(positionY) };

        DrawTextEx(font, text, pos, static_cast<float>(fontSize), spacing, color);
    }
}