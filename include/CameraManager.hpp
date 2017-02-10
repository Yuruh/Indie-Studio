//
// MyCamera.hpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Wed Apr 27 14:22:22 2016 Antoine Lempereur
// Last update Wed Jun  1 13:05:51 2016 Antoine Lempereur
//

#ifndef	CAMERAMANAGER_HPP_
# define CAMERAMANAGER_HPP_

# include	<OGRE/OgreCamera.h>
# include	<OGRE/OgreSceneManager.h>
# include 	<OGRE/OgreRenderWindow.h>
# include	"PlayableClass/Player.hpp"

# define	CAMERA_HEIGHT   1200
# define	TILT_VALUE	600
# define	RADIUS		100
# define	CAM_MAX_SPEED	4000
# define	CAM_MIN_SPEED	500

class   CameraManager
{
public:
  CameraManager( Ogre::SceneManager*, std::string const&);
  ~CameraManager();
  Ogre::Camera	*getCam() const;
  void		setMeanPosition(const std::map<ClassPlayer, Player*>&);
  void		setMeanLook(const std::map<ClassPlayer, Player*>&);
  void		setViewport(Ogre::RenderWindow &);
  void		setFinalPos(Ogre::Vector3 const&);
  void		updatePos(float);
private:
  Ogre::Camera	*_camera;
  Ogre::Vector3	_finalPos;
  Ogre::Vector3	_halfway;
  float		_dist;
  double	_speed;
  bool		_speedUp;
};

#endif
