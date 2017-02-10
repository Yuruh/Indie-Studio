//
// InputHandler.cpp for indie_studio in /home/desrum_m/code/epitech/S4/cpp_indie_studio/src/Events
// 
// Made by Martin Desrumaux
// Login   <desrum_m@epitech.net>
// 
// Started on  Mon May 23 02:37:38 2016 Martin Desrumaux
// Last update Sat Jun 04 23:06:46 2016 Martin Desrumaux
//

#include	<mutex>
#include	"Events/InputHandler.hpp"

InputHandler		*InputHandler::inputHandler_instance = NULL;

InputHandler		*InputHandler::instance()
{
  if (!inputHandler_instance)
    inputHandler_instance = new InputHandler();
  return (inputHandler_instance);
}

InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
  auto			it = this->mapped.begin();

  while (it != this->mapped.end())
  {
    delete (it->second);
    this->mapped.erase(it);
  }
}

void		InputHandler::handleInput()
{
  SDL_Event			event;

  while (SDL_PollEvent(&event))
  {
    this->_ceguiEvents.sendCEGUIEvents(event);
    for (auto it = this->mapped.begin(); it != this->mapped.end(); ++it)
    {
      if (it->second->execute(event) == true)
	break;
    }
  }
}

unsigned int	InputHandler::addInputHandler(ICommand *cmd)
{
  unsigned int		i = 0;
  auto			it = this->mapped.begin();

  while (it != this->mapped.end() && it->first == i)
  {
    ++it;
    ++i;
  }
  this->mapped[i] = cmd;
  return (i);
}

void		InputHandler::removeInputHandler(unsigned int id)
{
  ICommand	*tmp;

  try {
    tmp = this->mapped.at(id);
  } catch (std::out_of_range) {
    std::cout << "Trying to delete a non-existing id" << std::endl;
    return;
  }
  delete (tmp);
  this->mapped.erase(id);
}
