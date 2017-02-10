//
// Light.cpp for indie in /home/desrum_m/code/epitech/S4/cpp_indie_studio
// 
// Made by Martin Desrumaux
// Login   <desrum_m@epitech.net>
// 
// Started on  Mon May 30 15:12:19 2016 Martin Desrumaux
// Last update Mon May 30 15:12:36 2016 Martin Desrumaux
//

# include		"Light.hpp"

Light::Light()
{
}

Light::~Light()
{
}

Ogre::Light::LightTypes 	Light::getType() const
{
	return (this->_type);
}

double						Light::getRange() const
{
	return (this->_range);
}

double						Light::getX() const
{
	return (this->_x);
}

double						Light::getY() const
{
	return (this->_y);
}

double 						Light::getZ() const
{
	return (this->_z);
}

Ogre::Vector3				Light::getPos() const
{
	return (Ogre::Vector3(this->_x, this->_y, this->_z));
}

double						Light::getDr() const
{
	return (this->_dr);
}

double						Light::getDg() const
{
	return (this->_dg);
}

double						Light::getDb() const
{
	return (this->_db);
}

Ogre::ColourValue			Light::getDiff() const
{
	return (Ogre::ColourValue(this->_dr, this->_dg, this->_db));
}

double						Light::getSr() const
{
	return (this->_sr);
}

double						Light::getSg() const
{
	return (this->_sg);
}

double						Light::getSb() const
{
	return (this->_sb);
}

Ogre::ColourValue			Light::getSpec() const
{
	return (Ogre::ColourValue(this->_sr, this->_sg, this->_sb));
}

void						Light::setType(Ogre::Light::LightTypes type)
{
	this->_type = type;
}

void						Light::setRange(double range)
{
	this->_range = range;
}

void						Light::setX(double x)
{
	this->_x = x;
}

void						Light::setY(double y)
{
	this->_y = y;
}

void						Light::setZ(double z)
{
	this->_z = z;
}

void						Light::setDr(double dr)
{
	this->_dr = dr;
}

void						Light::setDg(double dg)
{
	this->_dg = dg;
}

void						Light::setDb(double db)
{
	this->_db = db;
}

void						Light::setSr(double sr)
{
	this->_sr = sr;
}

void						Light::setSg(double sg)
{
	this->_sg = sg;
}

void						Light::setSb(double sb)
{
	this->_sb = sb;
}
