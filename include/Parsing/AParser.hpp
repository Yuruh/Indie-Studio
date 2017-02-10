//
// AParser.hpp for gauntlet in /home/zanard_a/rendu/Projets_TEK2/cpp_gauntlet
//
// Made by Antoine Zanardi
// Login   <zanard_a@epitech.net>
//
// Started on  Tue May 15 14:06:45 2016 Antoine Zanardi
// Last update Mon May 30 19:55:14 2016 Raphael Thiebault
//

#ifndef		APARSER_HPP_
# define	APARSER_HPP_

# include	<iostream>
# include	<string>
# include	<fstream>
# include	<sstream>

class 		AParser
{
  protected:
  size_t	_nbLine;

  public:
  AParser();
  virtual	~AParser();

  void			parseFile(const std::string&);
  virtual void	parseData(std::string) = 0;

  std::string		trimLine(const std::string&) const;
  std::string		getFirstWord(const std::string&) const;
  std::string		toString(size_t) const;
  bool			isInt(const std::string&) const;
  void			nextValue(const std::string&, size_t&) const;
};

#endif		// !APARSER_HPP_
