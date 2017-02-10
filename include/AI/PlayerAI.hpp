//
// PlayerAI.hpp for  in /home/wasta-geek/rendu/CPP/cpp_indie_studio
//
// Made by Wasta-Geek
// Login   <ducate_c@epitech.net>
//
// Started on  Thu May 19 16:23:17 2016 Wasta-Geek
// Last update Sun Jun  5 19:10:17 2016 Antoine Lempereur
//

#ifndef		PlayerAI_HPP_
# define	PlayerAI_HPP_

#include	"IAI.hpp"
#include	"PlayerManager.hpp"
#include	"Mobs/ANonPlayable.hpp"
#include	"Room.hpp"

class				PlayerAI : public IAI
{
  const Room			*_room;
  PlayerAI();
public:
  ~PlayerAI();
  void				chooseAction(ACharacter*, const double&);
  static PlayerAI		*getInstance();
  void				setRoom(const Room*);
};

#endif		/* PlayerAI.hpp */
