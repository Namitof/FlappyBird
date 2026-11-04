#pragma once

#include "scenes/scene.h"

namespace ReyesCuadra
{
    // Prepara el boton para volver al menu (llamar una vez, despues de abrir la ventana)
    void InitCredits();

    // Revisa si el usuario quiere volver y devuelve la escena a la que hay que ir
    Scene UpdateCredits();

    // Dibuja los creditos del juego
    void DrawCredits();
}
