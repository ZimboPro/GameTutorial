#include <ServiceLocator.hpp>

IAudioProvider * ServiceLocator::_audioProvider = NULL;

IAudioProvider * ServiceLocator::GetAudio()
{
    return _audioProvider;
}

void ServiceLocator::RegisterServiceLocator(IAudioProvider * service)
{
    _audioProvider = service;
}