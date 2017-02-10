//
// PathFinding.hpp for  in /home/wasta-geek/rendu/CPP/cpp_indie_studio
// 
// Made by Wasta-Geek
// Login   <ducate_c@epitech.net>
// 
// Started on  Tue May 24 12:41:02 2016 Wasta-Geek
// Last update Fri Jun  3 11:00:13 2016 Wasta-Geek
//

#ifndef		PATH_FINDING_HPP_
# define	PATH_FINDING_HPP_

#include	<OGRE/OgreVector3.h>
#include	"ACharacter.hpp"
#include	"PlayableClass/Player.hpp"
#include	"Mobs/ANonPlayable.hpp"

class		PathFinding
{
public:
  enum move			{UP, DOWN, LEFT, RIGHT, NONE};
  struct			link
  {
    link(Ogre::Vector3 pos, double coutSinceBegin, double coutToEnd, double coutSumPrev)
      : pos(pos), coutSinceBegin(coutSinceBegin), coutToEnd(coutToEnd), coutSumPrev(coutSumPrev) {};
    link() {};
    Ogre::Vector3		pos;
    double			coutSinceBegin;
    double			coutToEnd;
    double			coutSumPrev;
  };
  PathFinding();
  ~PathFinding();
  static void		NextMove(ACharacter*, const Ogre::Vector3&, const double&, bool);
  static double		getDistance(const Ogre::Vector3&, const Ogre::Vector3&);
  static void		MoveObstacle(ACharacter*, const Ogre::Vector3&, double);
  static Ogre::Vector3	addNeighbour(const Ogre::Vector3&, const Ogre::Vector3&,
				     const double&, const double&, bool);
  static void		selectMin(std::vector<Ogre::Vector3>&, std::vector<Ogre::Vector3>&);
  static bool		checkEnd(const std::vector<Ogre::Vector3>&, const Ogre::Vector3&,
				 const double&, const double&);
  static Ogre::Vector3	getNearPlayer(const Ogre::Vector3&,
				      const std::pair<Ogre::Vector3, Player*>(&)[4]);
  static ANonPlayable	*getNearMob(const Ogre::Vector3&, const std::vector<ANonPlayable*>&);
  static bool		checkRay(ACharacter*, const ACharacter*);
  static bool		isInList(const std::vector<link>&, const Ogre::Vector3 &);
};

#endif		/* PathFinding.hpp */
