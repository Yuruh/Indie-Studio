#ifndef		PARSER_SCORE_HPP_
# define	PARSER_SCORE_HPP_

# include	<map>
# include	<regex>
# include	"AParser.hpp"

class ParserScore : public AParser
{
	typedef void(ParserScore::*ptr)(const std::string&);

  protected:
  std::map<std::string, size_t> 			 _result;
  std::map<std::string, ptr> 				 _fmap;
  std::map<std::string, std::regex> 	 	 _regexMap;
  std::smatch 								 _regexMatch;

  public:
  ParserScore();
  ~ParserScore();

  void	initRegex();

  void  parseWarrior(const std::string&);
  void  parseValkyrie(const std::string&);
  void  parseArcher(const std::string&);
  void  parseMage(const std::string&);

  void	parseData(std::string);

  const std::map<std::string, size_t> &getResult() const;
};

#endif		// !PARSER_SCORE_HPP_