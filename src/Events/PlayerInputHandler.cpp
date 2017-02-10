//
// PlayerInputHandler.cpp for indie_studio in /home/desrum_m/code/epitech/S4/cpp_indie_studio/src/Events
//
// Made by Martin Desrumaux
// Login   <desrum_m@epitech.net>
//
// Started on  Mon May 23 02:44:34 2016 Martin Desrumaux
// Last update Thu Jun 02 01:39:41 2016 Martin Desrumaux
//

#include		"Events/Commands.hpp"
#include		"Events/MoveCommands.hpp"
#include		"Events/PlayerInputHandler.hpp"
#include		"Events/InputHandler.hpp"

PlayerInputHandler::PlayerInputHandler(Player &player, const Controller &controller)
{
  unsigned int	id;

  if (controller.type == KEYBOARD)
  {
    this->movements = new KeyMoveCommand
      (player, SDLK_z, SDLK_s, SDLK_q, SDLK_d);
    id = InputHandler::instance()->addInputHandler(this->movements);
    this->layout.push_back(id);

    this->attacks = new AttackCommand(player, SDLK_SPACE, controller);
    id = InputHandler::instance()->addInputHandler(this->attacks);
    this->layout.push_back(id);

    this->specialAttacks = new SpecialAttackCommand(player, SDLK_b, controller);
    id = InputHandler::instance()->addInputHandler(this->specialAttacks);
    this->layout.push_back(id);
  }
  else if (controller.type == GAMECONTROLLER)
  {
    this->movements = new JoystickMoveCommand
      (player, static_cast<const GameController&>(controller).id);
    id = InputHandler::instance()->addInputHandler(this->movements);
    this->layout.push_back(id);

    this->attacks = new AttackCommand(player, MY_SDL_CONTROLLER_BUTTON_A, \
				      controller);
    id = InputHandler::instance()->addInputHandler(this->attacks);
    this->layout.push_back(id);

    this->specialAttacks = new SpecialAttackCommand(player, \
						    MY_SDL_CONTROLLER_BUTTON_B, \
						    controller);
    id = InputHandler::instance()->addInputHandler(this->specialAttacks);
    this->layout.push_back(id);
  }
  // IA
  else
  {
    this->movements = NULL;
  }
}

PlayerInputHandler::~PlayerInputHandler()
{
  auto it = this->layout.begin();
  while (it != this->layout.end())
  {
    InputHandler::instance()->removeInputHandler(*it);
    this->layout.erase(it);
  }
}

void				PlayerInputHandler::update(float timeSinceLastFrame)
{
  if (this->movements != NULL)
  {
    this->movements->update(timeSinceLastFrame);
    this->attacks->update(timeSinceLastFrame);
    this->specialAttacks->update(timeSinceLastFrame);
  }
}
