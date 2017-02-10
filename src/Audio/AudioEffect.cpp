//
// AudioEffect.cpp for indie in /home/archie/workspace/C++/cpp_indie_studio/src/Audio/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Wed May 25 12:11:11 2016 Corentin Descamps
// Last update Thu May 26 10:51:44 2016 Corentin Descamps
//

#include	"Audio/AudioEffect.hpp"

float	AudioEffect::m_volume = 100.0f;

AudioEffect::AudioEffect()
{

}

AudioEffect::~AudioEffect()
{

}

void		AudioEffect::loadSound(std::string const& sound, std::string const& filepath)
{
  this->m_sounds[sound] = sf::SoundBuffer();
  this->m_sounds[sound].loadFromFile(filepath);
}

void		AudioEffect::playSound(std::string const& sound)
{
  if (this->m_sound.getVolume() != this->m_volume)
    this->m_sound.setVolume(this->m_volume);
  this->m_sound.setBuffer(this->m_sounds[sound]);
  this->m_sound.play();
}

void		AudioEffect::setVolume(float volume)
{
  this->m_volume = volume;
}
