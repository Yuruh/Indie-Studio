//
// AnimatedLayout.cpp for indie in /home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio
//
// Made by Antoine Zanardi
// Login   <zanard_a@epitech.net>
//
// Started on  Sun Jun  5 22:22:47 2016 Antoine Zanardi
// Last update Sun Jun  5 22:22:49 2016 Antoine Zanardi
//

#include		"AnimatedLayout.hpp"

CEGUI::AnimatedLayout::AnimatedLayout(const std::string &layout)
{
	this->_layout = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(layout);
	this->setAlpha(0);
	this->_mode = FADE_IN;
}

CEGUI::AnimatedLayout::~AnimatedLayout()
{
}

void			CEGUI::AnimatedLayout::fade()
{
	if ((this->_mode == FADE_IN && this->_alpha >= 1) ||
		(this->_mode == FADE_OUT && this->_alpha <= 0))
	{
		this->_mode = FADE_IDLE;
		return;
	}
	if (this->_mode == FADE_IN)
		this->setAlpha(this->_alpha += 0.008);
	else if (this->_mode == FADE_OUT)
		this->setAlpha(this->_alpha -= 0.008);
}

double			CEGUI::AnimatedLayout::getAlpha() const
{
	return (this->_alpha);
}

void			CEGUI::AnimatedLayout::setAlpha(double alpha)
{
	this->_alpha = alpha;
	this->_layout->setAlpha(alpha);
}

CEGUI::Window*	CEGUI::AnimatedLayout::getLayout() const
{
	return (this->_layout);
}

CEGUI::Fade 	CEGUI::AnimatedLayout::getMode() const
{
	return (this->_mode);
}

void			CEGUI::AnimatedLayout::setMode(CEGUI::Fade mode)
{
	this->_mode = mode;
}
