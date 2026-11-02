#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "background/parallax_layer.h"

namespace ReyesCuadra
{
    // Fondo del gameplay con efecto parallax: cada capa se mueve a distinta velocidad para dar sensacion de profundidad
    struct Background
    {
        ParallaxLayer farLayer; // Capa mas lejana: edificios claros que se mueven lento
        ParallaxLayer midLayer; // Capa del medio: edificios mas bajos y oscuros que se mueven mas rapido
    };

    // Crea el fondo con todas sus capas en su posicion inicial
    Background CreateBackground(int screenWidth);

    // Desplaza cada capa del fondo segun su velocidad
    void UpdateBackground(Background& background, float deltaTime);

    // Dibuja las capas del fondo, de la mas lejana a la mas cercana
    void DrawBackground(const Background& background, int screenHeight);
}

#endif // BACKGROUND_H
