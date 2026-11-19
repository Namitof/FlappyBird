#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "raylib.h"

namespace ReyesCuadra
{
	void LoadResources();

	Font GetFont();
	Texture2D GetMenuBackground();

	void UnloadResources();
}

#endif // RESOURCE_MANAGER_H