#ifndef LIGHT_H
#define LIGHT_H

#include <SFML/Graphics.hpp>
#include "Vector3.h"
//#include "Color.h"

class Light
{
public:
	Light();
	Light(const Vector3& vec, sf::Color col);

	//Getter and Setter
	Vector3 getLightPosition();
	void setLightPosition(Vector3 v1);
	sf::Color getLightColor();
	void setLightColor(sf::Color col);

private:
	Vector3 m_Position;
	sf::Color m_Color;
};

#endif // !LIGHT_H