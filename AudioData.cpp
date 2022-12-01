#include "AudioData.h"
#include "RandGen.h"
#include <fstream>

AudioData::AudioData() :
	soundBuffers_(),
	musicFilePaths_(),
	music_(),
	soundPool_(16)
{
	this->load_("data/sounds.txt", "data/music.txt");
}

AudioData &AudioData::getInstance()
{
	static AudioData instance;
	return instance;
}

void AudioData::update()
{
	soundPool_.update();
}

void AudioData::playSound(Id id)
{
	if (soundPool_.isFull())
		return;

	sf::Sound *sound = new sf::Sound(soundBuffers_[id]);
	sound->setVolume(25.0f);
	sound->play();

	soundPool_.add(sound);
}

void AudioData::playRandomizedSound(Id id)
{
	if (soundPool_.isFull())
		return;

	sf::Sound *sound = new sf::Sound(soundBuffers_[id]);
	sound->setVolume(25.0f);
	sound->setPitch(
		std::uniform_real_distribution<float>(1.0f, 1.25f)(
			RandGen::getInstance().getEng()));
	sound->play();

	soundPool_.add(sound);
}

void AudioData::playMusic(Id id)
{
	music_.openFromFile(musicFilePaths_[id]);
	music_.setLoop(true);
	music_.setVolume(10.0f);
	music_.play();
}

void AudioData::stopMusic()
{
	music_.stop();
}

void AudioData::load_(
	const std::string &soundBuffersFilePath,
	const std::string &musicFilePathsFilePath)
{
	std::ifstream in(soundBuffersFilePath);

	if (!in.is_open())
	{
		printf("Failed to open \"%s\" in AudioData!", soundBuffersFilePath.c_str());
		return;
	}

	int32_t numSounds;
	in >> numSounds;

	while (numSounds--)
	{
		int32_t soundId;
		std::string soundFilePath;

		in >> soundId >> soundFilePath;

		sf::SoundBuffer soundBuffer;
		soundBuffer.loadFromFile(soundFilePath);

		soundBuffers_.emplace(soundId, std::move(soundBuffer));
	}

	in.close();

	in.open(musicFilePathsFilePath);

	if (!in.is_open())
	{
		printf("Failed to open \"%s\" in AudioData!", musicFilePathsFilePath.c_str());
		return;
	}

	int32_t numMusics;
	in >> numMusics;

	while (numMusics--)
	{
		int32_t musicId;
		std::string musicFilePath;

		in >> musicId >> musicFilePath;

		musicFilePaths_.emplace(musicId, std::move(musicFilePath));
	}

	in.close();
}