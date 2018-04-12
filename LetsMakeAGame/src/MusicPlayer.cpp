
#include "Globals.h"
#include "MusicPlayer.h"


MusicPlayer MusicPlayer::Instance;

MusicPlayer::MusicPlayer()
{
	m_currentvolume = Mix_VolumeMusic(-1);
}


MusicPlayer::~MusicPlayer()
{
	for (auto musictrack : m_musicTracks)
	{
		Mix_FreeMusic(musictrack.second);
	}
	m_musicTracks.clear();
}

void MusicPlayer::IncreaseVolume()
{
	if (m_currentvolume < MIX_MAX_VOLUME)
		SetVolume(m_currentvolume += 16);
}

void MusicPlayer::DecreaseVolume()
{
	if (m_currentvolume > 0)
		SetVolume(m_currentvolume -= 16);
}

void MusicPlayer::SetVolume(int volume)
{
	Mix_VolumeMusic(volume);
}

unsigned MusicPlayer::LoadSong(std::string filename)
{
	unsigned gid = std::hash<std::string>{}(filename);
	
	if (m_musicTracks.count(gid))
		return gid;

	auto song = Mix_LoadMUS(std::string(Globals::GetResourcePath() + "sound\\" + filename).c_str());

	m_musicTracks[gid] = song;

	return gid;
}

void MusicPlayer::PlaySong(unsigned id)
{
	if (m_musicTracks.count(id) > 0)
		Mix_PlayMusic(m_musicTracks[id], -1);
}

void MusicPlayer::StopPlaying()
{
	Mix_PauseMusic();
}

void MusicPlayer::UnloadSong(unsigned id)
{
	for (auto track : m_musicTracks)
	{
		if (m_musicTracks.count(id))
		{
			m_musicTracks.erase(track.first);
			break;
		}
	}
}

int MusicPlayer::GetVolumeNumber()
{
	return m_currentvolume / 16;
}
