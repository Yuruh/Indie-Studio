//
// MeleeAI.hpp for  in /home/wasta-geek/rendu/CPP/cpp_indie_studio
// 
// Made by Wasta-Geek
// Login   <ducate_c@epitech.net>
// 
// Started on  Thu May 19 16:23:17 2016 Wasta-Geek
// Last update Tue May 31 17:13:52 2016 Wasta-Geek
//

#ifndef		MeleeAI_HPP_
# define	MeleeAI_HPP_

#include	"IAI.hpp"
#include	"PlayerManager.hpp"
#include	"Mobs/ANonPlayable.hpp"

class					MeleeAI : public IAI
{
  MeleeAI();
  const PlayerManager			*_players;
  void					doAttack(ANonPlayable*, Player*) const;
public:
  ~MeleeAI();
  void					chooseAction(ACharacter*, const double&);
  static MeleeAI			*getInstance();
  void					setPlayers(const PlayerManager*);
};

#endif		/* MeleeAI.hpp */
