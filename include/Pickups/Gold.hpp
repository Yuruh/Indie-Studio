//
// Gold.hpp for indie in /home/archie/workspace/C++/cpp_indie_studio/include/Pickups/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Wed Jun  1 21:29:12 2016 Corentin Descamps
// Last update Fri Jun  3 17:39:05 2016 Corentin Descamps
//

#ifndef		GOLD_HPP_
# define	GOLD_HPP_

# include	"Pickups/Pickup.hpp"

class	Gold : public Pickup
{
public:
  Gold();
  Gold(Ogre::SceneManager* sceneManager, Ogre::SceneNode* node, Ogre::Vector3 const& pos);
  ~Gold();
protected:
  void		applyEffect(Player& player);
private:
  int		_value;
};

#endif		/* !GOLD_H_ */
