//
// MobFactory.hpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Fri May 20 16:59:45 2016 Antoine Lempereur
// Last update Wed Jun  1 21:54:54 2016 Antoine Lempereur
//

#ifndef MOB_FACTORY_HPP_
#define MOB_FACTORY_HPP_

#include <map>
#include <string>

#include "ANonPlayable.hpp"

class	ANonPlayable;

class MobFactory
{
private:
  std::map<std::string, ANonPlayable*(MobFactory::*)(void)> _fptr;
  ANonPlayable*	createZombie();
  ANonPlayable*	createArcher();
  ANonPlayable*	createBoss();
public:
  MobFactory();
  virtual ~MobFactory();
  ANonPlayable*	createMob(std::string const&);
};

#endif /* end of include guard: MOB_FACTORY_HPP_ */
