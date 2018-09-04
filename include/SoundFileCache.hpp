#ifndef SOUNDFILECACHE_HPP
#define SOUNDFILECACHE_HPP

#include <SFML/Audio.hpp>
#include <map>

class SoundFileCache
{
    public:
        SoundFileCache();
        ~SoundFileCache();

        sf::Sound GetSound(std::string name) const;
        sf::Music* GetSong(std::string name) const;

    private:
        static std::map<std::string, sf::SoundBuffer *> _sounds;
        static std::map<std::string, sf::Music *> _music;

        struct SoundFileDeallocator
        {
            void operator()(const std::pair<std::string,sf::SoundBuffer*> & p)
            {
                delete p.second;
            }
        };
        struct MusicFileDeallocator
        {
            void operator()(const std::pair<std::string,sf::Music*> & p) 
            {
                delete p.second;
            }
        };
  
        template <typename T>
        struct Deallocator
        {
            void operator()(const std::pair<std::string,T> &p) 
            {
                delete p.second;
            }
        };
};

class SoundNotFoundExeception : public std::runtime_error
{
    public:
        SoundNotFoundExeception(std::string const& msg):
            std::runtime_error(msg)
        {}
};

#endif