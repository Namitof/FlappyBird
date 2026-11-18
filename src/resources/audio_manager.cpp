#include "audio_manager.h"

#include "raylib.h"

namespace ReyesCuadra
{
	//Constante
	const float MUSIC_MAX_VOLUME = 0.4f;

	//Sonidos
	static Sound hitFloor;
	static Sound hitPipe;
	static Sound gameOver;
	static Sound birdOne;
	static Sound birdTwo;
	static Sound select;

	//Musica
	static Music gameMusic;
	static Music menuMusic;

	void LoadAudio()
	{
		hitFloor = LoadSound("res/Sounds/hitFloor.wav");
		hitPipe = LoadSound("res/Sounds/hitPipe.wav");
		gameOver = LoadSound("res/Sounds/gameOver.wav");
		birdOne = LoadSound("res/Sounds/bird.wav");
		birdTwo = LoadSound("res/Sounds/bird.wav");
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

	Sound GetBirdOneSound()
	{
		return birdOne;
	}

	Sound GetBirdTwoSound()
	{
		return birdTwo;
	}

	Sound GetSelectSound()
	{
		return select;
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

	void PlayBirdOneSound()
	{
		if (!IsSoundPlaying(birdOne))
		{
			PlaySound(birdOne);
		}
	}

	void PlayBirdTwoSound()
	{
		if (!IsSoundPlaying(birdTwo))
		{
			PlaySound(birdTwo);
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
			SetMusicVolume(menuMusic, MUSIC_MAX_VOLUME);
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
			SetMusicVolume(gameMusic, MUSIC_MAX_VOLUME);
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

	void UnloadAudio()
	{
		UnloadSound(hitFloor);
		UnloadSound(hitPipe);
		UnloadSound(gameOver);
		UnloadSound(birdOne);
		UnloadSound(birdTwo);
		UnloadSound(select);

		UnloadMusicStream(gameMusic);
		UnloadMusicStream(menuMusic);
	}
}