//
// AudioEffect.hpp for indie in /home/archie/workspace/C++/cpp_indie_studio/include/Audio/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Wed May 25 11:21:57 2016 Corentin Descamps
// Last update Thu May 26 10:52:02 2016 Corentin Descamps
//

#ifndef		AUDIOEFFECT_HPP_
# define	AUDIOEFFECT_HPP_

# include	<string>
# include	<map>
# include	<SFML/Audio.hpp>

class	AudioEffect
{
public:
  AudioEffect();
  ~AudioEffect();
  void		loadSound(std::string const& soundName, std::string const& filepath);
  void		playSound(std::string const& sound);
  void		setVolume(float volume);

private:
  static float	m_volume;

  std::map<std::string, sf::SoundBuffer>	m_sounds;
  sf::Sound		m_sound;
};

#endif		/* !AUDIOEFFECT_HPP_ */
