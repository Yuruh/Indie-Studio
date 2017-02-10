//
// Object.hpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Wed Apr 27 16:35:43 2016 Antoine Lempereur
// Last update Mon May  2 20:27:44 2016 Antoine Lempereur
//

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <OgreEntity.h>
#include <OgreSceneManager.h>

namespace Display
{
  class Object
  {
  private:
    Ogre::Entity  *entity;
    Ogre::SceneNode *node;
  public:
    Object(Ogre::Entity *, Ogre::SceneNode *, Ogre::Vector3 const& pos = Ogre::Vector3(0, 0, 0),
      Ogre::Vector3 const& rot = Ogre::Vector3(0, 0, 0), Ogre::Vector3 const& size = Ogre::Vector3(1, 1, 1));
    virtual ~Object();
    void  setPosition(Ogre::Vector3 const&);
    void  setCastShadows(bool cast) { this->entity->setCastShadows(cast); }
    void  setMaterialName(std::string const& name) { this->entity->setMaterialName(name); }
    void  moveX(double);
    void  moveY(double);
    void  moveZ(double);
  };
};

//class AnimatedObject heritant de object ?

#endif
