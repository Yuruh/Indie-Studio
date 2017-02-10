//
// Elem.cpp for indie in /home/archie/workspace/C++/cpp_indie_studio/src/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Fri May 13 13:17:48 2016 Corentin Descamps
// Last update Fri Jun  3 18:01:24 2016 Wasta-Geek
//

#include "Elem.hpp"

Elem::Elem()
{
  this->_entity = NULL;
  this->_node = NULL;
  this->_facingDir = Ogre::Vector3::UNIT_X;
}

Elem::~Elem()
{
}

void 	Elem::setEntity(Ogre::Entity *entity)
{
  this->_entity = entity;
  this->_entity->setQueryFlags(NON_BLOCKING);
}

void	Elem::setPosition(Ogre::Vector3 const& pos)
{
  if (this->_node)
    this->_node->setPosition(pos);
}

// TODO: stocker la taille à part car elle dépend de la taille du modle 3d ?
// throw une exception si node ou entity est null ?
void 	Elem::setNode(Ogre::SceneNode *node,
		      Ogre::Vector3 const& pos,
		      Ogre::Vector3 const& rot,
		      Ogre::Vector3 const& size)
{
  this->_node = node;
  this->_node->setPosition(pos);
  this->_node->pitch(Ogre::Degree(rot.x));
  this->_node->yaw(Ogre::Degree(rot.y));
  this->_node->roll(Ogre::Degree(rot.z));

  Ogre::AxisAlignedBox charAABB = this->_entity->getBoundingBox();
  Ogre::Vector3 min = charAABB.getMinimum();
  Ogre::Vector3 max = charAABB.getMaximum();
  Ogre::Vector3 oldSize(fabs(max.x - min.x), fabs(max.y - min.y), fabs(max.z - min.z));

  this->_node->setScale(1.0 / oldSize.y * size.y, 1.0 / oldSize.y * size.y, 1.0 / oldSize.y * size.y);

  if (this->_entity)
    this->_node->attachObject(this->_entity);
}

void	Elem::setManualScale(Ogre::Vector3 const& size)
{
  Ogre::AxisAlignedBox charAABB = this->_entity->getBoundingBox();
  Ogre::Vector3 min = charAABB.getMinimum();
  Ogre::Vector3 max = charAABB.getMaximum();
  Ogre::Vector3 oldSize(fabs(max.x - min.x), fabs(max.y - min.y), fabs(max.z - min.z));

  this->_node->setScale(1.0 / oldSize.x * size.x, 1.0 / oldSize.y * size.y, 1.0 / oldSize.z * size.z);
}

void   Elem::setCrossing(BoundingBox crossing)
{
  this->_crossing = crossing;
}

void			Elem::detachEntity()
{
  if (this->_entity && this->_entity->isAttached())
    this->_node->detachObject(this->_entity);
}

void			Elem::attachEntity()
{
  if (this->_entity && !this->_entity->isAttached())
    this->_node->attachObject(this->_entity);
}

void			  Elem::yaw(Ogre::Degree const &value)
{
  this->_node->yaw(value);
}

Ogre::Vector3		Elem::getPos() const
{
  return (this->_node->_getDerivedPosition());
}

void	Elem::setRelativePos(Ogre::Vector3 const &to_set)
{
  return (this->_node->_setDerivedPosition(to_set));
}

//verifier que le getscale correspond à la vrai size, pas un truc par rapoort à la taille du modele
Ogre::Vector3		Elem::getDim() const
{
  return (this->_node->getScale());
}

Ogre::Quaternion	Elem::getRot() const
{
  return (this->_node->getOrientation());
}

void 			Elem::move(Ogre::Vector3 const& value)
{
  this->_node->translate(value);
}

void			Elem::rotate(Ogre::Quaternion const& value)
{
  this->_node->rotate(value);
}

Ogre::Vector3		Elem::getDirection() const
{
  return (this->getRot() * this->_facingDir);
}

void			Elem::rotate(Ogre::Vector3 const& dir)
{
  Ogre::Vector3 src = this->getRot() * this->_facingDir;

  if (1.0 + src.dotProduct(dir) < 0.0001)
    this->yaw(Ogre::Degree(180));
  else
  {
    Ogre::Quaternion quat = src.getRotationTo(dir);
    this->_node->rotate(quat);
  }
}

Ogre::Entity*		Elem::getEntity() const
{
  return (this->_entity);
}

Ogre::SceneNode*  Elem::getNode() const
{
  return (this->_node);
}

BoundingBox       Elem::getCrossing() const
{
  return (this->_crossing);
}
