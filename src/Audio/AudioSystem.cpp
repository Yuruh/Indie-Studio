//
// AudioSystem.cpp for indie in /home/archie/workspace/C++/cpp_indie_studio/src/Audio/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Thu May 19 16:08:59 2016 Corentin Descamps
// Last update Mon May 23 16:35:46 2016 Raphael Thiebault
//

#include	"Audio/AudioSystem.hpp"

AudioSystem::AudioSystem()
{
  this->m_music.setRelativeToListener(false);
}

AudioSystem::~AudioSystem()
{

}

void		AudioSystem::loadMusic(std::string const& filename)
{
  if (!this->m_music.openFromFile(filename))
    return;
}

void		AudioSystem::playMusic()
{
  this->m_music.setLoop(true);
  this->m_music.play();
}

void		AudioSystem::playMusic(std::string const& filename)
{
  this->loadMusic(filename);
  this->m_music.setLoop(true);
  this->m_music.play();
}

void		AudioSystem::stopMusic()
{
  this->m_music.setLoop(false);
  this->m_music.stop();
}

void		AudioSystem::setMusicVolume(float volume)
{
  this->m_music.setVolume(volume);
}

float		AudioSystem::getMusicVolume() const
{
  return (this->m_music.getVolume());
}

void		AudioSystem::setGlobalVolume(float volume)
{
  sf::Listener::setGlobalVolume(volume);
}

float		AudioSystem::getGlobalVolume() const
{
  return (sf::Listener::getGlobalVolume());
}
