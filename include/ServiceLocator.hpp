#ifndef SERVICELOCATOR_HPP
#define SERVICELOCATOR_HPP

#include <IAudioProvider.hpp>

class ServiceLocator
{
    public:
        static IAudioProvider * GetAudio();
        static void RegisterServiceLocator(IAudioProvider * service);

    private:
        static IAudioProvider * _audioProvider;
};

#endif