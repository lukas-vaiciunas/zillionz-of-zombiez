#pragma once

#include "SoundPool.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>
#include <unordered_map>

class AudioData
{
public:
	typedef uint16_t Id;

	AudioData(const AudioData &) = delete;
	AudioData &operator=(const AudioData &) = delete;

	static AudioData &getInstance();

	void update();

	void playSound(Id id);
	void playRandomizedSound(Id id);

	void playMusic(Id id);
	void stopMusic();
private:
	std::unordered_map<Id, sf::SoundBuffer> soundBuffers_;
	std::unordered_map<Id, std::string> musicFilePaths_;

	sf::Music music_;

	SoundPool soundPool_;

	AudioData();
	~AudioData() {}

	void load_(
		const std::string &soundBuffersFilePath,
		const std::string &musicFilePathsFilePath);
};