//
// HealthPotion.hpp for indie in /home/archie/workspace/C++/cpp_indie_studio/include/Pickups/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Fri Jun  3 21:34:23 2016 Corentin Descamps
// Last update Fri Jun  3 21:47:35 2016 Corentin Descamps
//

#ifndef		HEALTHPOTION_HPP_
# define	HEALTHPOTION_HPP_

# include	"Pickups/Pickup.hpp"

class	HealthPotion : public Pickup
{
public:
  HealthPotion();
  HealthPotion(Ogre::SceneManager* sceneManager, Ogre::SceneNode* node, Ogre::Vector3 const& pos);
  ~HealthPotion();
protected:
  void		applyEffect(Player& player);
private:
  int		_value;
};

#endif		/* !HEALTHPOTION_HPP_ */
