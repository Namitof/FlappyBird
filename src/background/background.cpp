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

    // Capa mas cercana: casas bajas y oscuras, que se mueven mas rapido que todas porque son las que estan mas cerca.
    // Son bajas para no tapar la zona por donde vuela el jugador
    static const float NEAR_LAYER_BLOCK_HEIGHTS[] = { 45.0f, 60.0f, 35.0f, 55.0f, 40.0f, 65.0f, 50.0f, 38.0f, 58.0f, 42.0f, 52.0f, 36.0f };
    static const float NEAR_LAYER_SPEED = 150.0f;
    static const Color NEAR_LAYER_COLOR = { 80, 125, 150, 255 };

    Background CreateBackground(int screenWidth)
    {
        Background background;

        const int farLayerBlockCount = static_cast<int>(std::size(FAR_LAYER_BLOCK_HEIGHTS));
        const int midLayerBlockCount = static_cast<int>(std::size(MID_LAYER_BLOCK_HEIGHTS));
        const int nearLayerBlockCount = static_cast<int>(std::size(NEAR_LAYER_BLOCK_HEIGHTS));

        background.farLayer = CreateParallaxLayer(FAR_LAYER_BLOCK_HEIGHTS, farLayerBlockCount, FAR_LAYER_SPEED, FAR_LAYER_COLOR, screenWidth);
        background.midLayer = CreateParallaxLayer(MID_LAYER_BLOCK_HEIGHTS, midLayerBlockCount, MID_LAYER_SPEED, MID_LAYER_COLOR, screenWidth);
        background.nearLayer = CreateParallaxLayer(NEAR_LAYER_BLOCK_HEIGHTS, nearLayerBlockCount, NEAR_LAYER_SPEED, NEAR_LAYER_COLOR, screenWidth);

        return background;
    }

    void UpdateBackground(Background& background, float deltaTime)
    {
        UpdateParallaxLayer(background.farLayer, deltaTime);
        UpdateParallaxLayer(background.midLayer, deltaTime);
        UpdateParallaxLayer(background.nearLayer, deltaTime);
    }

    void DrawBackground(const Background& background, int screenHeight)
    {
        // Cada capa se dibuja encima de la anterior, asi la mas cercana queda adelante
        DrawParallaxLayer(background.farLayer, screenHeight);
        DrawParallaxLayer(background.midLayer, screenHeight);
        DrawParallaxLayer(background.nearLayer, screenHeight);
    }
}