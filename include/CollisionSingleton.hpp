//
// CollisionSingleton.hpp for indie in /home/archie/workspace/C++/cpp_indie_studio/include/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Sat May 21 15:40:47 2016 Corentin Descamps
// Last update Wed Jun  1 19:56:13 2016 Corentin Descamps
//

#ifndef		COLLISIONSINGLETON_HPP_
# define	COLLISIONSINGLETON_HPP_

# include	<vector>

# include	"Elem.hpp"

struct	t_collide
{
  bool	collided;
  Elem*	elem;
};

//TODO:
// - flags for opti

class	CollisionSingleton
{
public:
  ~CollisionSingleton();

  static CollisionSingleton&	getInstance();
  CollisionSingleton(CollisionSingleton const&)		= delete;
  void		operator=(CollisionSingleton const&)	= delete;

  void		addEntity(Elem *elem);
  void		removeEntity(Elem *elem);
  t_collide	check_collision(Elem const& self, Ogre::Vector3 const& fromPos, Ogre::Vector3 const& toPoint, QueryFlags flags = EVERYTHING);
  t_collide	check_ray_collision(Elem const& self, Ogre::Vector3& direction, float range, QueryFlags flags = EVERYTHING);
  t_collide	check_box_collision(Elem const& self, Elem const& ignore, QueryFlags flags = EVERYTHING);
  std::vector<t_collide> check_sphere_collision(Elem const& ignore, Ogre::Vector3 const& position, float radius, QueryFlags flags = EVERYTHING);

private:
  CollisionSingleton();

  std::vector<Elem *>	m_elems;
};

#endif		/* !COLLISIONSINGLETON_HPP_ */
