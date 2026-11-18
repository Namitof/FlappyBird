#include "resource_manager.h"

#include "raylib.h"

namespace ReyesCuadra
{
	// Fuentes
	static Font font;

	// Texturas
	static Texture2D logo;
	static Texture2D bird;
	static Texture2D obstacleTop;
	static Texture2D obstacleBottom;

	void LoadResources()
	{
		font = LoadFont("res/Font/DeadFontWalking.otf");
	}

	Font GetFont()
	{
		return font;
	}

	void UnloadResources()
	{
		UnloadFont(font);
	}
}