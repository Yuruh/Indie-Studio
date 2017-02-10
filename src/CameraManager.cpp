//
// CameraManager.cpp for indie in /home/raphicci/Documents/TEK2-2015/cpp_indie_studio/src/
//
// Made by Raphael Thiebault
// Login   <thieba_r@epitech.net>
//
// Started on  Fri May 20 13:38:36 2016 Raphael Thiebault
// Last update Wed Jun  1 13:20:38 2016 Antoine Lempereur
//

#include	<cmath>
#include	"CameraManager.hpp"

CameraManager::CameraManager(Ogre::SceneManager *manager, std::string const& name)
{
  this->_camera = manager->createCamera(name);
  this->_camera->setPosition(0.0, CAMERA_HEIGHT, -TILT_VALUE);
  this->_finalPos = this->_camera->getPosition();
  this->_camera->lookAt(0, 0, 0);
  this->_speed = CAM_MIN_SPEED;
  this->_speedUp = true;
}

// TODO const -->
Ogre::Camera	*CameraManager::getCam() const
{
  return (_camera);
}

void		CameraManager::updatePos(float timeSinceLastFrame)
{
  Ogre::Vector3	dir;

  if (this->_camera->getPosition() == this->_finalPos)
    {
      this->_speed = CAM_MIN_SPEED;
      this->_speedUp = true;
      return;
    }
  if (this->_camera->getPosition().distance(this->_finalPos) <= 10)
    {
      this->_finalPos = this->_camera->getPosition();
      this->_speed = CAM_MIN_SPEED;
      this->_speedUp = true;
      return;
    }
  if (this->_camera->getPosition().distance(this->_halfway) <= 100)
    {
      this->_speedUp = false;
      this->_dist = this->_finalPos.distance(this->_halfway);
    }
  dir = this->_finalPos - this->_camera->getPosition();
  dir.normalise();
  Ogre::Vector3	applyed(dir * timeSinceLastFrame * this->_speed);

  float speedModifyer = (this->_camera->getPosition() + applyed).distance(this->_camera->getPosition()) / this->_dist * (CAM_MAX_SPEED - CAM_MIN_SPEED);
  this->_camera->move(applyed);
  if (this->_speedUp)
    this->_speed += speedModifyer;
  else
    this->_speed -= speedModifyer;
  if (this->_speed < CAM_MIN_SPEED)
    this->_speed = CAM_MIN_SPEED;
  if (this->_speed > CAM_MAX_SPEED + 500) // Si la camera part en live, ça l'arretera
    {
      this->_camera->setPosition(this->_finalPos);
      this->_speed = CAM_MIN_SPEED;
      this->_speedUp = true;
    }
}

void		CameraManager::setFinalPos(Ogre::Vector3 const& value)
{
  this->_finalPos = value;
  Ogre::Vector3 dir = this->_finalPos - this->_camera->getPosition();
  dir.normalise();
  this->_halfway = this->_camera->getPosition() + this->_finalPos.distance(this->_camera->getPosition()) * 0.5 * dir;
  this->_dist = this->_halfway.distance(this->_camera->getPosition());
}

void		CameraManager::setViewport(Ogre::RenderWindow &win)
{
  Ogre::Viewport *vp = win.addViewport(_camera);
  vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
  _camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}
