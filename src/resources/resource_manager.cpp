#include "resource_manager.h"

#include "raylib.h"

namespace ReyesCuadra
{
	// Fuentes
	static Font font;

	// Texturas
	static Texture2D menuBackground;

	void LoadResources()
	{
		font = LoadFont("res/Font/DeadFontWalking.otf");
		menuBackground = LoadTexture("res/Background/Background.png");
	}

	Font GetFont()
	{
		return font;
	}

	Texture2D GetMenuBackground()
	{
		return menuBackground;
	}

	void UnloadResources()
	{
		UnloadFont(font);
		UnloadTexture(menuBackground);
	}
}