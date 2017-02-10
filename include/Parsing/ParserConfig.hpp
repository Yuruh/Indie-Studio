//
// ParserConfig.hpp for indie in /home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio
//
// Made by Antoine Zanardi
// Login   <zanard_a@epitech.net>
//
// Started on  Tue May 24 18:22:03 2016 Antoine Zanardi
// Last update Tue May 24 18:22:04 2016 Antoine Zanardi
//

#ifndef		PARSER_CONFIG_HPP_
# define	PARSER_CONFIG_HPP_

# include	<map>
# include	<regex>
# include	"AParser.hpp"

class ParserConfig : public AParser
{

  typedef void(ParserConfig::*ptr)(const std::string&);

  protected:
  std::map<std::string, double> 			 _result;
  std::map<std::string, ptr> 				   _fmap;
  std::map<std::string, std::regex> 	 _regexMap;
  std::smatch 								         _regexMatch;

  public:
  ParserConfig();
  ~ParserConfig();

  void	initRegex();

  void  parseSon(const std::string&);
  void  parseVolume(const std::string&);
  void  parseMusique(const std::string&);
  void  parseMute(const std::string&);
  void  parseOmbre(const std::string&);
  void  parseDebug(const std::string&);

  void	parseData(std::string);

  const std::map<std::string, double> &getResult() const;
};

#endif		//!PARSER_CONFIG_HPP_
