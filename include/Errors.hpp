//
// Errors.hpp for indie in /home/archie/workspace/C++/cpp_indie_studio/include/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Tue May  3 09:26:44 2016 Corentin Descamps
// Last update Tue May  3 09:31:29 2016 Corentin Descamps
//

#ifndef		ERRORS_HPP_
# define	ERRORS_HPP_

# include	<stdexcept>
# include	<string>

class	GauntletError : public std::exception
{
public:
  GauntletError(std::string const& message = "");
  ~GauntletError() throw() {}
  virtual const char*	what() const throw();

protected:
  std::string	m_message;
};

#endif		/* !ERRORS_HPP_ */
