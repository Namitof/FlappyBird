#ifndef PARALLAX_LAYER_H
#define PARALLAX_LAYER_H

#include "raylib.h"

namespace ReyesCuadra
{
    // Capa del fondo formada por una fila de bloques rectangulares apoyados en el borde inferior de la pantalla.
    // Los bloques forman un patron que ocupa todo el ancho de la pantalla y se repite sin cortes mientras la capa se desplaza a la izquierda
    struct ParallaxLayer
    {
        const float* blockHeights; // Alto de cada bloque del patron, de izquierda a derecha
        int blockCount;
        float blockWidth;          // Ancho de cada bloque, calculado para que el patron mida lo mismo que la pantalla
        float scrollOffset;        // Cuanto se desplazo el patron hacia la izquierda (va de 0 al ancho del patron)
        float speed;               // Velocidad de desplazamiento en pixeles por segundo
        Color color;
    };

    // Crea una capa con el patron de bloques recibido, repartiendo los bloques en todo el ancho de la pantalla
    ParallaxLayer CreateParallaxLayer(const float* blockHeights, int blockCount, float speed, Color color, int screenWidth);

    // Desplaza la capa hacia la izquierda segun su velocidad; al recorrer un patron entero vuelve a empezar
    void UpdateParallaxLayer(ParallaxLayer& layer, float deltaTime);

    // Dibuja la capa como rectangulos, repitiendo el patron para que no quede ningun hueco en la pantalla
    void DrawParallaxLayer(const ParallaxLayer& layer, int screenHeight);
}

#endif // PARALLAX_LAYER_H