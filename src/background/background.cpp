#include "background/background.h"

#include <iterator>

#include "raylib.h"

namespace ReyesCuadra
{
    // Capa lejana: edificios altos y claros que se mueven lento, porque estan lejos
    static const float FAR_LAYER_BLOCK_HEIGHTS[] = { 150.0f, 190.0f, 130.0f, 220.0f, 170.0f, 140.0f, 205.0f, 160.0f, 185.0f, 135.0f };
    static const float FAR_LAYER_SPEED = 30.0f;
    static const Color FAR_LAYER_COLOR = { 160, 205, 225, 255 }; // Celeste apenas mas oscuro que el cielo, para que parezca lejano

    Background CreateBackground(int screenWidth)
    {
        Background background;

        const int farLayerBlockCount = static_cast<int>(std::size(FAR_LAYER_BLOCK_HEIGHTS));

        background.farLayer = CreateParallaxLayer(FAR_LAYER_BLOCK_HEIGHTS, farLayerBlockCount, FAR_LAYER_SPEED, FAR_LAYER_COLOR, screenWidth);

        return background;
    }

    void UpdateBackground(Background& background, float deltaTime)
    {
        UpdateParallaxLayer(background.farLayer, deltaTime);
    }

    void DrawBackground(const Background& background, int screenHeight)
    {
        DrawParallaxLayer(background.farLayer, screenHeight);
    }
}
