//
// AParser.cpp for indie in /home/zanard_a/rendu/Projets_TEK2/cpp_Core
//
// Made by Antoine Zanardi
// Login   <zanard_a@epitech.net>
//
// Started on  Tue May 15 14:07:10 2016 Antoine Zanardi
// Last update Mon May 30 15:20:55 2016 Martin Desrumaux
//

#include		"Parsing/AParser.hpp"
#include		"Parsing/ParserError.hpp"

AParser::AParser()
{
  this->_nbLine = 1;
}

AParser::~AParser()
{
}

void			AParser::parseFile(const std::string &filepath)
{
  std::fstream		file;
  std::string		line;

  file.open(filepath.c_str());
  if (!file.is_open())
    throw ParserError("Couldn't open the file " + filepath);
  while (std::getline(file, line))
    {
      this->parseData(this->trimLine(line));
      this->_nbLine++;
    }
  file.close();
}

std::string		AParser::trimLine(const std::string &str) const
{
  size_t		first;
  size_t		last;

  first = str.find_first_not_of(" \t");
  last = str.find_last_not_of(" \t") + 1;
  if (first == std::string::npos || last == std::string::npos)
    return ("");
  return (str.substr(first, last));
}

bool			AParser::isInt(const std::string &line) const
{
  if (line.find_first_not_of("0123456789") != std::string::npos)
    return (false);
  return (true);
}

void			AParser::nextValue(const std::string &line, size_t &it) const
{
  while (line[it] != ' ' && line[it] != '\t' && line[it] != '\0')
    it++;
  while (line[it] == ' ' || line[it] == '\t')
    it++;
}

std::string		AParser::toString(size_t value) const
{
  std::stringstream stream;

  stream << value;
  return stream.str();
}

std::string 	AParser::getFirstWord(const std::string &line) const
{
  return (line.substr(0, line.find_first_of(" =\t\0")));
}
