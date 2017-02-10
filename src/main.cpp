//
// main.cpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/src/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Mon May  2 11:40:29 2016 Antoine Lempereur
// Last update Sun Jun 05 01:51:07 2016 Martin Desrumaux
//

#include "Parsing/ParserMap.hpp"
#include "Parsing/ParserError.hpp"
#include "Application.hpp"

int						main()
{
  srand(time(NULL) * getpid());
  try
    {
      Display::Application		app;
      app.go();
    }
  catch (Ogre::Exception const& e)
    {
      std::cerr << e.what() << " from " << e.getSource() << std::endl;
      return (0);
    }
  catch (std::exception const& e)
    {
      std::cerr << e.what() << std::endl;
      return (0);
    }
  return (0);
}
