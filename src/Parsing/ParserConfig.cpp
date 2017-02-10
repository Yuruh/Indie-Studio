//
// ParserConfig.cpp for indie in /home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio
//
// Made by Antoine Zanardi
// Login   <zanard_a@epitech.net>
//
// Started on  Tue May 24 18:21:50 2016 Antoine Zanardi
// Last update Mon May 30 15:23:54 2016 Martin Desrumaux
//

#include	"Parsing/ParserConfig.hpp"
#include	"Parsing/ParserError.hpp"

ParserConfig::ParserConfig()
{
  this->initRegex();
}

ParserConfig::~ParserConfig()
{
}

void		ParserConfig::initRegex()
{
  std::string   regD;
  std::string 	regFilename;

  regD = "((?:-?[0-9]+)|(?:-?[0-9]+\\.[0-9]+))";
  regFilename = "([a-z0-9A-Z_.\\/-]+)";
  this->_regexMap["SON"] = std::regex("^SON=" + regD + "$");
  this->_regexMap["VOLUME"] = std::regex("^VOLUME=" + regD + "$");
  this->_regexMap["MUSIQUE"] = std::regex("^MUSIQUE=" + regD + "$");
  this->_regexMap["MUTE"] = std::regex("^MUTE=(0|1)$");
  this->_regexMap["OMBRE"] = std::regex("^OMBRE=([1-3])$");
  this->_regexMap["DEBUG"] = std::regex("^DEBUG=(0|1)$");
  this->_fmap["SON"] = &ParserConfig::parseSon;
  this->_fmap["MUSIQUE"] = &ParserConfig::parseMusique;
  this->_fmap["VOLUME"] = &ParserConfig::parseVolume;
  this->_fmap["MUTE"] = &ParserConfig::parseMute;
  this->_fmap["OMBRE"] = &ParserConfig::parseOmbre;
  this->_fmap["DEBUG"] = &ParserConfig::parseDebug;
}

void    ParserConfig::parseSon(const std::string &value)
{
  std::vector<std::string>  s_elem;
  float                     son;

  std::regex_match(value, this->_regexMatch, this->_regexMap["SON"]);
  if (this->_regexMatch.size() != 2)
    return;
  for (auto it = this->_regexMatch.begin(); it != this->_regexMatch.end(); it++)
    s_elem.push_back(*it);
  son = atof(s_elem[1].c_str());
  if (son < 0 || son > 1)
    return;
  this->_result["SON"] = son;
}

void    ParserConfig::parseVolume(const std::string &value)
{
  std::vector<std::string>  s_elem;
  float                     volume;

  std::regex_match(value, this->_regexMatch, this->_regexMap["VOLUME"]);
  if (this->_regexMatch.size() != 2)
    return;
  for (auto it = this->_regexMatch.begin(); it != this->_regexMatch.end(); it++)
    s_elem.push_back(*it);
  volume = atof(s_elem[1].c_str());
  if (volume < 0 || volume > 1)
    return;
  this->_result["VOLUME"] = volume;
}

void    ParserConfig::parseMusique(const std::string &value)
{
  std::vector<std::string>  s_elem;
  float                     musique;

  std::regex_match(value, this->_regexMatch, this->_regexMap["MUSIQUE"]);
  if (this->_regexMatch.size() != 2)
    return;
  for (auto it = this->_regexMatch.begin(); it != this->_regexMatch.end(); it++)
    s_elem.push_back(*it);
  musique = atof(s_elem[1].c_str());
  if (musique < 0 || musique > 1)
    return;
  this->_result["MUSIQUE"] = musique;
}

void    ParserConfig::parseMute(const std::string &value)
{
  std::vector<std::string>  s_elem;
  float                     mute;

  std::regex_match(value, this->_regexMatch, this->_regexMap["MUTE"]);
  if (this->_regexMatch.size() != 2)
    return;
  for (auto it = this->_regexMatch.begin(); it != this->_regexMatch.end(); it++)
    s_elem.push_back(*it);
  mute = atof(s_elem[1].c_str());
  this->_result["MUTE"] = mute;
}

void    ParserConfig::parseOmbre(const std::string &value)
{
  std::vector<std::string>  s_elem;
  float                     ombre;

  std::regex_match(value, this->_regexMatch, this->_regexMap["OMBRE"]);
  if (this->_regexMatch.size() != 2)
    return;
  for (auto it = this->_regexMatch.begin(); it != this->_regexMatch.end(); it++)
    s_elem.push_back(*it);
  ombre = atof(s_elem[1].c_str());
  this->_result["OMBRE"] = ombre;
}

void    ParserConfig::parseDebug(const std::string &value)
{
  std::vector<std::string>  s_elem;
  float                     debug;

  std::regex_match(value, this->_regexMatch, this->_regexMap["DEBUG"]);
  if (this->_regexMatch.size() != 2)
    return;
  for (auto it = this->_regexMatch.begin(); it != this->_regexMatch.end(); it++)
    s_elem.push_back(*it);
  debug = atof(s_elem[1].c_str());
  this->_result["DEBUG"] = debug;
}

void		ParserConfig::parseData(std::string line)
{
  std::map<std::string, ptr>::iterator		it;
  std::string					value;

  line = this->trimLine(line);
  if (line.empty() || line[0] == '#')
    return;
  if ((it = this->_fmap.find(this->getFirstWord(line))) != this->_fmap.end())
    (this->*(this->_fmap.find(this->getFirstWord(line))->second))(line);
  else
    std::cout << "INCONNU = " << line << std::endl;
}

const std::map<std::string, double> &ParserConfig::getResult() const
{
  return (this->_result);
}
