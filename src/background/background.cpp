#include "background/background.h"

#include <iterator>

#include "raylib.h"

namespace ReyesCuadra
{
    // Capa lejana: edificios altos y claros que se mueven lento, porque estan lejos
    static const float FAR_LAYER_BLOCK_HEIGHTS[] = { 150.0f, 190.0f, 130.0f, 220.0f, 170.0f, 140.0f, 205.0f, 160.0f, 185.0f, 135.0f };
    static const float FAR_LAYER_SPEED = 30.0f;
    static const Color FAR_LAYER_COLOR = { 160, 205, 225, 255 }; // Celeste apenas mas oscuro que el cielo, para que parezca lejano

    // Capa del medio: edificios mas bajos y oscuros, que se mueven mas rapido porque estan mas cerca.
    // Tiene otra cantidad de bloques que la lejana, para que los dos patrones no se vean calcados
    static const float MID_LAYER_BLOCK_HEIGHTS[] = { 90.0f, 120.0f, 75.0f, 110.0f, 95.0f, 130.0f, 80.0f, 105.0f };
    static const float MID_LAYER_SPEED = 70.0f;
    static const Color MID_LAYER_COLOR = { 120, 170, 195, 255 };

    Background CreateBackground(int screenWidth)
    {
        Background background;

        const int farLayerBlockCount = static_cast<int>(std::size(FAR_LAYER_BLOCK_HEIGHTS));
        const int midLayerBlockCount = static_cast<int>(std::size(MID_LAYER_BLOCK_HEIGHTS));

        background.farLayer = CreateParallaxLayer(FAR_LAYER_BLOCK_HEIGHTS, farLayerBlockCount, FAR_LAYER_SPEED, FAR_LAYER_COLOR, screenWidth);
        background.midLayer = CreateParallaxLayer(MID_LAYER_BLOCK_HEIGHTS, midLayerBlockCount, MID_LAYER_SPEED, MID_LAYER_COLOR, screenWidth);

        return background;
    }

    void UpdateBackground(Background& background, float deltaTime)
    {
        UpdateParallaxLayer(background.farLayer, deltaTime);
        UpdateParallaxLayer(background.midLayer, deltaTime);
    }

    void DrawBackground(const Background& background, int screenHeight)
    {
        // Cada capa se dibuja encima de la anterior, asi la mas cercana queda adelante
        DrawParallaxLayer(background.farLayer, screenHeight);
        DrawParallaxLayer(background.midLayer, screenHeight);
    }
}
