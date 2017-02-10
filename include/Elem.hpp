//
// Elem.hpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Mon May  2 20:28:18 2016 Antoine Lempereur
// Last update Fri Jun  3 16:56:30 2016 Antoine Lempereur
//

#ifndef			ELEM_HPP_
# define		ELEM_HPP_

# include		<iostream>
# include		<string>
# include		<OGRE/OgreVector3.h>
# include		<OGRE/OgreEntity.h>
# include		<OGRE/OgreSceneManager.h>
# include		<algorithm>

enum Type
{
  VOID = 0,
  WALL,
  GROUND,
};

enum QueryFlags
{
  PLAYER = 1 << 0,
  ENEMY = 1 << 1,
  BLOCKING = 1 << 2,
  NON_BLOCKING = 1 << 3,
  PICKUP = 1 << 4,
  EVERYTHING = ~0
};

enum BoundingBox {
    TRANS,
    PICK,
    SOLID,
 };

class Elem
{
public:
  Elem();
  virtual ~Elem();

  Ogre::Vector3		   getPos() const;
  Ogre::Vector3 	   getDim() const;
  Ogre::Quaternion   getRot() const;
  Ogre::Vector3		   getDirection() const;
  Ogre::SceneNode 	 *getNode() const;
  BoundingBox        getCrossing() const;

  void			setEntity(Ogre::Entity *);
  void 			setNode(Ogre::SceneNode *node, Ogre::Vector3 const& pos = Ogre::Vector3(0, 0, 0),
				Ogre::Vector3 const& rot = Ogre::Vector3(0, 0, 0), Ogre::Vector3 const& size = Ogre::Vector3(50, 50, 50));
  void			setManualScale(Ogre::Vector3 const&);
  void      setCrossing(BoundingBox);
  void			move(Ogre::Vector3 const&);
  void			rotate(Ogre::Quaternion const&);
  void			rotate(Ogre::Vector3 const&);
  void			yaw(Ogre::Degree const&);
  Ogre::Entity*		getEntity() const;
  void			detachEntity();
  void			attachEntity();
  void			setPosition(Ogre::Vector3 const&);
  void			setRelativePos(Ogre::Vector3 const&);
  bool			isColliding() const;

protected:
  Ogre::Entity		*_entity;
  Ogre::Vector3		_facingDir;
  Ogre::SceneNode	*_node;
  BoundingBox     _crossing;
};

#endif		//!ELEM_HPP_
