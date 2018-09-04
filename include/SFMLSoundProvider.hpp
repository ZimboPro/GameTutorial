#ifndef SFMLSOUNDPROVIDER_HPP
#define SFMLSOUNDPROVIDER_HPP

#include <IAudioProvider.hpp>

class SFMLSoundProvider : public IAudioProvider
{
    public:
        SFMLSoundProvider();
        virtual ~SFMLSoundProvider();
        void PlaySound(std::string filename);
        void PlaySong(std::string filename, bool looping = false);
        void StopAllSounds();

        bool IsSoundPlaying();
        bool IsSongPlaying();
    
    private:
        static const int MAX_SOUND_CHANNELS = 5;

        sf::SoundBuffer _soundBuffer;
        sf::Sound _sound;
        sf::Music _song;
};

#endif