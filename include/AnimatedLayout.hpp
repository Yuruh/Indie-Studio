#ifndef		ANIMATEDLAYOUT_HPP_
# define	ANIMATEDLAYOUT_HPP_

# include 	<CEGUI/CEGUI.h>
# include	<string>
# include	<iostream>

namespace CEGUI
{
	enum Fade 
	{ 
		FADE_IN,
		FADE_OUT,
		FADE_IDLE,
	};
	class  		AnimatedLayout
	{
	public:
		AnimatedLayout(const std::string&);
		~AnimatedLayout();
	
		void			fade();

		double			getAlpha() const;
		void			setAlpha(double);
		CEGUI::Window*	getLayout() const;
		Fade 			getMode() const;
		void 			setMode(Fade);

	protected:
		double			_alpha;
		Fade 			_mode;
		CEGUI::Window*	_layout;
	};
}

#endif		//!ANIMATEDLAYOUT_HPP_