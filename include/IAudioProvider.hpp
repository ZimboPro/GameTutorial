#ifndef IAUDIOPROVIDER_HPP
#define IAUDIOPROVIDER_HPP

#include <SFML/Audio.hpp>
#include <string>

class IAudioProvider
{
    public:
        // virtual ~IAudioProvider();
        virtual void PlaySound(std::string name) = 0;
        virtual void PlaySong(std::string name, bool looping) = 0;
        virtual void StopAllSounds() = 0;

        virtual bool IsSoundPlaying() = 0;
        virtual bool IsSongPlaying() = 0;
};

#endif