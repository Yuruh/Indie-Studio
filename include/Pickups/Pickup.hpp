//
// Pickup.hpp for indie in /home/archie/workspace/C++/cpp_indie_studio/include/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Tue May 31 14:52:18 2016 Corentin Descamps
// Last update Sun Jun  5 00:13:01 2016 Antoine Lempereur
//

#ifndef		PICKUP_HPP_
# define	PICKUP_HPP_

# include	"PlayableClass/Player.hpp"

class	Pickup : public Elem
{
protected:
  AudioEffect	_audio;
public:
  Pickup();
  ~Pickup();
  virtual void		applyEffect(Player& player) = 0;
};

#endif		/* !PICKUP_HPP_ */
