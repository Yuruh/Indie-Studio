//
// ANonPlayable.cpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/src/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Sun May 22 17:02:06 2016 Antoine Lempereur
// Last update Fri May 27 17:03:15 2016 Wasta-Geek
//

#include "Mobs/ANonPlayable.hpp"

ANonPlayable::ANonPlayable()
{

}

ANonPlayable::~ANonPlayable()
{

}

void	ANonPlayable::ActionAI(const double &timeSinceLastFrame)
{
  this->_AI->chooseAction(this, timeSinceLastFrame);
}
