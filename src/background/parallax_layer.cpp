#include "background/parallax_layer.h"

#include "raylib.h"

namespace ReyesCuadra
{
    // Cantidad de veces que se dibuja el patron: con dos copias, una al lado de la otra, siempre se cubre toda la pantalla
    static const int PATTERN_COPIES = 2;

    // Devuelve el ancho total del patron de bloques
    static float GetPatternWidth(const ParallaxLayer& layer);

    ParallaxLayer CreateParallaxLayer(const float* blockHeights, int blockCount, float speed, Color color, int screenWidth)
    {
        ParallaxLayer layer;

        layer.blockHeights = blockHeights;
        layer.blockCount = blockCount;
        layer.blockWidth = static_cast<float>(screenWidth) / static_cast<float>(blockCount);
        layer.scrollOffset = 0.0f;
        layer.speed = speed;
        layer.color = color;

        return layer;
    }

    void UpdateParallaxLayer(ParallaxLayer& layer, float deltaTime)
    {
        layer.scrollOffset += layer.speed * deltaTime;

        // Cuando el patron se corrio un ancho entero, la segunda copia quedo justo donde arranco la primera:
        // se vuelve atras ese ancho y el movimiento sigue sin que se note el salto
        const float patternWidth = GetPatternWidth(layer);

        if (layer.scrollOffset >= patternWidth)
        {
            layer.scrollOffset -= patternWidth;
        }
    }

    void DrawParallaxLayer(const ParallaxLayer& layer, int screenHeight)
    {
        const float patternWidth = GetPatternWidth(layer);
        const float screenBottom = static_cast<float>(screenHeight);

        for (int copyIndex = 0; copyIndex < PATTERN_COPIES; copyIndex++)
        {
            // Cada copia arranca donde termina la anterior, corrida segun cuanto avanzo la capa
            const float copyStartX = static_cast<float>(copyIndex) * patternWidth - layer.scrollOffset;

            for (int blockIndex = 0; blockIndex < layer.blockCount; blockIndex++)
            {
                const float blockHeight = layer.blockHeights[blockIndex];

                Rectangle block;
                block.x = copyStartX + static_cast<float>(blockIndex) * layer.blockWidth;
                block.y = screenBottom - blockHeight; // Los bloques se apoyan en el borde inferior de la pantalla
                block.width = layer.blockWidth;
                block.height = blockHeight;

                DrawRectangleRec(block, layer.color);
            }
        }
    }

    static float GetPatternWidth(const ParallaxLayer& layer)
    {
        return layer.blockWidth * static_cast<float>(layer.blockCount);
    }
}