#include "resource_manager.h"

#include <raylib.h>

namespace ReyesCuadra
{
	//Sonidos
	static Sound hitFloor;
	static Sound hitPipe;
	static Sound gameOver;
	static Sound bird;
	static Sound select;

	//Musica
	static Music gameMusic;
	static Music menuMusic;

	void LoadResources()
	{
		hitFloor = LoadSound("res/Sounds/hitFloor.wav");
		hitPipe = LoadSound("res/Sounds/hitPipe.wav");
		gameOver = LoadSound("res/Sounds/gameOver.wav");
		bird = LoadSound("res/Sounds/bird.wav");
		select = LoadSound("res/Sounds/select.wav");

		gameMusic = LoadMusicStream("res/Music/gameMusic.ogg");
		menuMusic = LoadMusicStream("res/Music/menuMusic.ogg");
	}

	Sound GetHitFloorSound()
	{
		return hitFloor;
	}

	Sound GetHitPipeSound()
	{
		return hitPipe;
	}

	Sound GetGameOverSound()
	{
		return gameOver;
	}

	Sound GetBirdSound()
	{
		return bird;
	}

	Sound GetSelectSound()
	{
		return bird;
	}

	Music GetGameMusic()
	{
		return gameMusic;
	}

	Music GetMenuMusic()
	{
		return menuMusic;
	}

	void PlayHitFloorSound()
	{
		if (!IsSoundPlaying(hitFloor))
		{
			PlaySound(hitFloor);
		}
	}

	void PlayHitPipeSound()
	{
		if (!IsSoundPlaying(hitPipe))
		{
			PlaySound(hitPipe);
		}
	}

	void PlayGameOverSound()
	{
		if (!IsSoundPlaying(gameOver))
		{
			PlaySound(gameOver);
		}
	}

	void PlayBirdSound()
	{
		if (!IsSoundPlaying(bird))
		{
			PlaySound(bird);
		}
	}

	void PlaySelectSound()
	{
		if (!IsSoundPlaying(select))
		{
			PlaySound(select);
		}
	}

	void PlayMenuMusic()
	{
		if (!IsMusicStreamPlaying(menuMusic))
		{
			PlayMusicStream(menuMusic);
		}
		else
		{
			UpdateMusicStream(menuMusic);
		}
	}

	void PlayGameMusic()
	{
		if (!IsMusicStreamPlaying(gameMusic))
		{
			PlayMusicStream(gameMusic);
		}
		else
		{
			UpdateMusicStream(gameMusic);
		}
	}

	void StopMenuMusic()
	{
		if (IsMusicStreamPlaying(menuMusic))
		{
			StopMusicStream(menuMusic);
		}
	}

	void StopGameMusic()
	{
		if (IsMusicStreamPlaying(gameMusic))
		{
			StopMusicStream(gameMusic);
		}
	}

	void SoundsTurnOn()
	{
		SetMasterVolume(1.0f);
	}

	void SoundsTurnOff()
	{
		SetMasterVolume(0.0f);
	}

	void UnloadResources()
	{
		UnloadSound(hitFloor);
		UnloadSound(hitPipe);
		UnloadSound(gameOver);
		UnloadSound(bird);
		UnloadSound(select);

		UnloadMusicStream(gameMusic);
		UnloadMusicStream(menuMusic);
	}
}