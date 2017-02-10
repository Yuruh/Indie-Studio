//
// Errors.cpp for indie in /home/archie/workspace/C++/cpp_indie_studio/src/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Tue May  3 09:32:26 2016 Corentin Descamps
// Last update Wed May 25 23:55:21 2016 Antoine Lempereur
//

#include	"Errors.hpp"

GauntletError::GauntletError(std::string const& message)
{
  this->m_message = message;
}

const char*	GauntletError::what() const throw()
{
  return (this->m_message.c_str());
}
