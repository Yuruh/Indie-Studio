//
// ParserScore.cpp for indie in /home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio
//
// Made by Antoine Zanardi
// Login   <zanard_a@epitech.net>
//
// Started on  Sun Jun  5 22:21:20 2016 Antoine Zanardi
// Last update Sun Jun  5 22:21:21 2016 Antoine Zanardi
//

#include	"Parsing/ParserScore.hpp"
#include	"Parsing/ParserError.hpp"

ParserScore::ParserScore()
{
  this->initRegex();
}

ParserScore::~ParserScore()
{
}

void		ParserScore::initRegex()
{
  this->_regexMap["WARRIOR"] = std::regex("^WARRIOR=([0-9]+)$");
  this->_regexMap["ARCHER"] = std::regex("^ARCHER=([0-9]+)$");
  this->_regexMap["MAGE"] = std::regex("^MAGE=([0-9]+)$");
  this->_regexMap["VALKYRIE"] = std::regex("^VALKYRIE=([0-9]+)$");
  this->_fmap["WARRIOR"] = &ParserScore::parseWarrior;
  this->_fmap["ARCHER"] = &ParserScore::parseArcher;
  this->_fmap["MAGE"] = &ParserScore::parseMage;
  this->_fmap["VALKYRIE"] = &ParserScore::parseValkyrie;
}

void    ParserScore::parseWarrior(const std::string &value)
{
  std::vector<std::string>  s_elem;
  size_t					warrior_score;

  std::regex_match(value, this->_regexMatch, this->_regexMap["WARRIOR"]);
  if (this->_regexMatch.size() != 2)
    return;
  for (auto it = this->_regexMatch.begin(); it != this->_regexMatch.end(); it++)
    s_elem.push_back(*it);
  warrior_score = atoi(s_elem[1].c_str());
  this->_result["WARRIOR"] = warrior_score;
}

void    ParserScore::parseArcher(const std::string &value)
{
  std::vector<std::string>  s_elem;
  size_t					archer_score;

  std::regex_match(value, this->_regexMatch, this->_regexMap["ARCHER"]);
  if (this->_regexMatch.size() != 2)
    return;
  for (auto it = this->_regexMatch.begin(); it != this->_regexMatch.end(); it++)
    s_elem.push_back(*it);
  archer_score = atoi(s_elem[1].c_str());
  this->_result["ARCHER"] = archer_score;
}

void    ParserScore::parseMage(const std::string &value)
{
  std::vector<std::string>  s_elem;
  size_t					mage_score;

  std::regex_match(value, this->_regexMatch, this->_regexMap["MAGE"]);
  if (this->_regexMatch.size() != 2)
    return;
  for (auto it = this->_regexMatch.begin(); it != this->_regexMatch.end(); it++)
    s_elem.push_back(*it);
  mage_score = atoi(s_elem[1].c_str());
  this->_result["MAGE"] = mage_score;
}

void    ParserScore::parseValkyrie(const std::string &value)
{
  std::vector<std::string>  s_elem;
  size_t					valkyrie_score;

  std::regex_match(value, this->_regexMatch, this->_regexMap["VALKYRIE"]);
  if (this->_regexMatch.size() != 2)
    return;
  for (auto it = this->_regexMatch.begin(); it != this->_regexMatch.end(); it++)
    s_elem.push_back(*it);
  valkyrie_score = atoi(s_elem[1].c_str());
  this->_result["VALKYRIE"] = valkyrie_score;
}

void		ParserScore::parseData(std::string line)
{
  std::map<std::string, ptr>::iterator		it;
  std::string								value;

  line = this->trimLine(line);
  if (line.empty() || line[0] == '#')
    return;
  if ((it = this->_fmap.find(this->getFirstWord(line))) != this->_fmap.end())
    (this->*(this->_fmap.find(this->getFirstWord(line))->second))(line);
  else
    std::cout << "INCONNU = " << line << std::endl;
}

const std::map<std::string, size_t> &ParserScore::getResult() const
{
  return (this->_result);
}
