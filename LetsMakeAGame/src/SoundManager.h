#pragma once

#include "Globals.h"
#include "SDL_mixer.h"
#include <string>
#include <list>

struct SoundListing
{
	Mix_Chunk* sound;
	unsigned id;
};

const int ExplosionSound = 1000,
		PowerupSound = 1001,
		ShootSound = 1002,
		ErkSound = 1003;

class SoundManager
{
	std::list<SoundListing> Sounds;
	SoundManager();
	void SetVolume(int volume);
	int m_currentvolume;
public:
	const enum Sounds{Explosion = 1000, Powerup = 1001, Shoot = 1002, Erk = 1003};
	~SoundManager();
	void Init();
	void IncreaseVolume();
	void DecreaseVolume();
	void LoadSound(unsigned id, std::string file);
	void PlayASound(unsigned id);
	int GetVolumeNumber();

	static SoundManager Instance;
};