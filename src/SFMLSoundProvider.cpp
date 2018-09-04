#include <SFMLSoundProvider.hpp>

SFMLSoundProvider::SFMLSoundProvider()
{
    this->_sound.setVolume(100.0f);
}

SFMLSoundProvider::~SFMLSoundProvider()
{}

void SFMLSoundProvider::PlaySound(std::string filename)
{
    if (this->_soundBuffer.getDuration().asSeconds() == 0)
        this->_soundBuffer.loadFromFile(filename);
    if (this->_sound.getStatus() == sf::Sound::Playing)
        this->_sound.stop();
    _sound.setBuffer(this->_soundBuffer);
    _sound.play();
}

void SFMLSoundProvider::PlaySong(std::string filename, bool looping)
{
    this->_song.openFromFile(filename);
    this->_song.setLoop(looping);
    this->_song.play();
}

void SFMLSoundProvider::StopAllSounds()
{
    if (this->_sound.getStatus() == sf::Sound::Playing)
        this->_sound.stop();
    if (this->_song.getStatus() == sf::Music::Playing)
        this->_song.stop();
}

bool SFMLSoundProvider::IsSoundPlaying()
{
    return this->_sound.getStatus() == sf::Sound::Playing;
}

bool SFMLSoundProvider::IsSongPlaying()
{
    return this->_song.getStatus() == sf::Music::Playing;
}