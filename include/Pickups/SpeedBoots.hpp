//
// SpeedBoots.hpp for indie in /home/archie/workspace/C++/cpp_indie_studio/include/PlayableClass/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Sun Jun  5 19:01:09 2016 Corentin Descamps
// Last update Sun Jun  5 19:02:43 2016 Corentin Descamps
//

#ifndef		SPEEDBOOTS_HPP_
# define	SPEEDBOOTS_HPP_

# include	"Pickups/Pickup.hpp"

class	SpeedBoots : public Pickup
{
public:
  SpeedBoots();
  SpeedBoots(Ogre::SceneManager* sceneManager, Ogre::SceneNode* node, Ogre::Vector3 const& pos);
  ~SpeedBoots();

  void		applyEffect(Player& player);
private:
  int		_value;
};

#endif		/* !SPEEDBOOTS_HPP_ */
