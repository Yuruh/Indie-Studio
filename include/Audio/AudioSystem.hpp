//
// AudioSystem.hpp for indie in /home/archie/workspace/C++/cpp_indie_studio/include/Audio/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Thu May 19 16:05:58 2016 Corentin Descamps
// Last update Thu May 19 16:22:25 2016 Corentin Descamps
//

#ifndef		AUDIOSYSTEM_HPP_
# define	AUDIOSYSTEM_HPP_

# include	<SFML/Audio.hpp>

class	AudioSystem
{
public:
  AudioSystem();
  ~AudioSystem();

  void		loadMusic(std::string const& filename);
  void		playMusic();
  void		playMusic(std::string const& filename);
  void		stopMusic();
  
  void		setMusicVolume(float volume);
  float		getMusicVolume() const;

  void		setGlobalVolume(float volume);
  float		getGlobalVolume() const;

private:
  sf::Music	m_music;
};

#endif		/* !AUDIOSYSTEM_HPP_ */
