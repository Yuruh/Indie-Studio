//
// IAI.hpp for  in /home/wasta-geek/rendu/CPP/cpp_indie_studio
// 
// Made by Wasta-Geek
// Login   <ducate_c@epitech.net>
// 
// Started on  Thu May 19 16:16:24 2016 Wasta-Geek
// Last update Fri May 27 17:58:01 2016 Wasta-Geek
//

#ifndef		IAI_HPP_
# define	IAI_HPP_

#include	"ACharacter.hpp"

class		ACharacter;

class		IAI
{
public:
  virtual ~IAI() {};
  virtual void	chooseAction(ACharacter*,const double&) = 0;
};

#endif		/* IAI.hpp */
