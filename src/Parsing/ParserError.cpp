//
// ParserError.cpp for indie in /home/desrum_m/code/epitech/S4/cpp_indie_studio
// 
// Made by Martin Desrumaux
// Login   <desrum_m@epitech.net>
// 
// Started on  Mon May 30 15:24:11 2016 Martin Desrumaux
// Last update Mon May 30 15:24:13 2016 Martin Desrumaux
//

#include "Parsing/ParserError.hpp"

ParserError::ParserError(std::string msg) throw() : _msg("Parser Error: " + msg)
{
}

ParserError::~ParserError()
{
}

const char		*ParserError::what() const throw()
{
  return (this->_msg.c_str());
}
