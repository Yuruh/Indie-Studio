//
// PickupFactory.hpp for PickupFactory in /home/archie/workspace/C++/cpp_indie_studio/include/Pickups/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Fri Jun  3 17:18:13 2016 Corentin Descamps
// Last update Sun Jun  5 19:04:48 2016 Corentin Descamps
//

#ifndef		PICKUPFACTORY_HPP_
# define	PICKUPFACTORY_HPP_

# include	<cstdlib>
# include	<ctime>

# include	"Pickups/Pickup.hpp"
# include	"Pickups/Gold.hpp"
# include	"Pickups/HealthPotion.hpp"
# include	"Pickups/AttackPotion.hpp"
# include	"Pickups/SpeedBoots.hpp"

class	PickupFactory
{
public:
  ~PickupFactory();
  static PickupFactory&	getInstance();
  void		init(Ogre::SceneManager *sceneManager);
  Pickup*	getRandomPickup(Ogre::SceneNode* node, Ogre::Vector3 const& pos);
  Pickup*	createGold(Ogre::SceneNode* node, Ogre::Vector3 const& pos);
  Pickup*	createHealthPot(Ogre::SceneNode* node, Ogre::Vector3 const& pos);
  Pickup*	createAttackPot(Ogre::SceneNode* node, Ogre::Vector3 const& pos);
  Pickup*	createSpeedBoots(Ogre::SceneNode* node, Ogre::Vector3 const& pos);

private:
  PickupFactory();
  Ogre::SceneManager*	_sceneManager;
  std::vector<Pickup* (PickupFactory::*)(Ogre::SceneNode*, Ogre::Vector3 const& pos)>	_factory;
};

#endif		/* !PICKUPFACTORY_HPP_ */
