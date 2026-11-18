#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "raylib.h"

namespace ReyesCuadra
{
	void LoadAudio();

	Sound GetHitFloorSound();
	Sound GetHitPipeSound();
	Sound GetGameOverSound();
	Sound GetBirdOneSound();
	Sound GetBirdTwoSound();
	Sound GetSelectSound();

	Music GetGameMusic();
	Music GetMenuMusic();

	void PlayHitFloorSound();
	void PlayHitPipeSound();
	void PlayGameOverSound();
	void PlayBirdOneSound();
	void PlayBirdTwoSound();
	void PlaySelectSound();

	void PlayMenuMusic();
	void PlayGameMusic();

	void StopMenuMusic();
	void StopGameMusic();

	void SoundsTurnOn();
	void SoundsTurnOff();

	void UnloadAudio();
}

#endif // AUDIO_MANAGER_H