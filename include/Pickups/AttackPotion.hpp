//
// AttackPotion.hpp for indie in /home/archie/workspace/C++/cpp_indie_studio/include/Pickups/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Sat Jun  4 10:11:08 2016 Corentin Descamps
// Last update Sat Jun  4 10:19:58 2016 Corentin Descamps
//

#ifndef		ATTACKPOTION_HPP_
# define	ATTACKPOTION_HPP_

# include	"Pickups/Pickup.hpp"

class	AttackPotion : public Pickup
{
public:
  AttackPotion();
  AttackPotion(Ogre::SceneManager* sceneManager, Ogre::SceneNode* node, Ogre::Vector3 const& pos);
  ~AttackPotion();

  void		applyEffect(Player& player);
private:
  int		_value;
};


#endif		/* !ATTACKPOTION_HPP_ */
