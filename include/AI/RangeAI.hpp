//
// RangeAI.hpp for  in /home/wasta-geek/rendu/CPP/cpp_indie_studio
// 
// Made by Wasta-Geek
// Login   <ducate_c@epitech.net>
// 
// Started on  Thu May 19 16:23:17 2016 Wasta-Geek
// Last update Tue May 31 17:14:19 2016 Wasta-Geek
//

#ifndef		RangeAI_HPP_
# define	RangeAI_HPP_

#include	"IAI.hpp"
#include	"PlayerManager.hpp"
#include	"Mobs/ANonPlayable.hpp"

class				RangeAI : public IAI
{
  const PlayerManager		*_players;
  // void				doAttack(ANonPlayable*, Player*, const double&) const;
public:
  RangeAI();
  ~RangeAI();
  void				chooseAction(ACharacter*, const double&);
  static RangeAI		*getInstance();
  void				setPlayers(const PlayerManager*);
};

#endif		/* RangeAI.hpp */
