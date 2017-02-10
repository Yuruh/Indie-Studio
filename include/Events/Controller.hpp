/*
** Controller.h for indie_studio in /home/desrum_m/code/epitech/S4/cpp_indie_studio/include/Events
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  Wed May 25 22:51:22 2016 Martin Desrumaux
** Last update Thu May 26 18:13:21 2016 Martin Desrumaux
*/

#ifndef		CONTROLLER_HPP_
# define	CONTROLLER_HPP_

# include	"PlayableClass/Player.hpp"
# include	"SDL.h"
# include	"PlayableClass/ClassPlayer.hpp"

enum ControllerType
{
  KEYBOARD,
  GAMECONTROLLER,
  IA
};

struct Controller
{
  Controller(ControllerType type): type(type) {}
  ControllerType	type;
};

struct KeyboardController : public Controller
{
  KeyboardController(): Controller(KEYBOARD) {}
};

struct IAController : public Controller
{
  IAController(): Controller(IA) {}
};

struct GameController : public Controller
{
  GameController(SDL_JoystickID id) : Controller(GAMECONTROLLER), id(id) {}
  SDL_JoystickID		id;
};

struct ControllerPlayer
{
  ControllerPlayer(Controller *controller, ClassPlayer player):
    controller(controller), player(player) {}
  Controller	*controller;
  ClassPlayer	player;
};

#endif		// !CONTROLLER_HPP_
