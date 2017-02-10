#ifndef			LIGHT_HPP_
# define		LIGHT_HPP_

# include		<iostream>
# include		<string>
# include		<OGRE/OgreLight.h>
# include		<OGRE/OgreColourValue.h>

	class Light
	{
	public:
		Light();
		~Light();

		Ogre::Light::LightTypes	getType() const;
		double					getRange() const;
		double					getX() const;
		double					getY() const;
		double					getZ() const;
		Ogre::Vector3 			getPos() const;
		double					getDr() const;
		double					getDg() const;
		double					getDb() const;
		Ogre::ColourValue 		getDiff() const;
		double					getSr() const;
		double					getSg() const;
		double					getSb() const;
		Ogre::ColourValue 		getSpec() const;

		void					setType(Ogre::Light::LightTypes);
		void					setRange(double);
		void					setX(double);
		void					setY(double);
		void					setZ(double);
		void					setDr(double);
		void					setDg(double);
		void					setDb(double);
		void					setSr(double);
		void					setSg(double);
		void					setSb(double);

	protected:
		Ogre::Light::LightTypes	_type;
		double 					_range;
		double					_x;
		double					_y;
		double					_z;
		double					_dr;
		double					_dg;
		double					_db;
		double					_sr;
		double					_sg;
		double					_sb;
	};

#endif		//!LIGHT_HPP_
