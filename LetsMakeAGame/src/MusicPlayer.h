#pragma once

#include "SDL_mixer.h"
#include <string>
#include <map>


class MusicPlayer
{
	std::map<unsigned, Mix_Music*> m_musicTracks;
	MusicPlayer();
	void SetVolume(int volume);
	int m_currentvolume;
public:
	~MusicPlayer();
	void IncreaseVolume();
	void DecreaseVolume();
	unsigned LoadSong( std::string filename);
	void PlaySong(unsigned id);
	void StopPlaying();
	void UnloadSong(unsigned id);
	int GetVolumeNumber();

	static MusicPlayer Instance;
};