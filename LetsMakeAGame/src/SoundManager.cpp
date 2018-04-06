
#include "SoundManager.h"

SoundManager SoundManager::Instance;

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
	for (auto sound : Sounds)
	{
		Mix_FreeChunk(sound.sound);
	}
}

void SoundManager::Init()
{
	SoundManager::Instance.LoadSound(Sounds::Explosion, "explosion.wav");
	SoundManager::Instance.LoadSound(Sounds::Powerup, "Powerup.wav");
	SoundManager::Instance.LoadSound(Sounds::Shoot, "Shoot.wav");
	SoundManager::Instance.LoadSound(Sounds::Erk, "erk.wav");
}

void SoundManager::IncreaseVolume()
{
	if (m_currentvolume < MIX_MAX_VOLUME)
		SetVolume(max(m_currentvolume += 16, MIX_MAX_VOLUME));
}

void SoundManager::DecreaseVolume()
{
	if (m_currentvolume > 0)
		SetVolume(min(m_currentvolume -= 16, 0));
}

void SoundManager::SetVolume(int volume)
{
	Mix_Volume(-1, volume);
}

void SoundManager::LoadSound(unsigned id, std::string file)
{
	std::string filePath = std::string(Globals::GetResourcePath() + "sound\\" + file);

	SoundListing soundListing;
	soundListing.id = id;
	soundListing.sound = Mix_LoadWAV(filePath.c_str());

	Sounds.push_back(soundListing);

	m_currentvolume = Mix_Volume(-1, -1);
}

void SoundManager::PlayASound(unsigned id)
{
	for (auto sound : Sounds)
	{
		if (sound.id == id)
		{
			Mix_PlayChannel(-1, sound.sound, 0);
			break;
		}
	}
}

int SoundManager::GetVolumeNumber()
{
	return m_currentvolume/16;
}
