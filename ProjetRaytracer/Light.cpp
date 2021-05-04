#include "Light.h"

Light::Light()
	: m_Position(Vector3(0,0,0))
	, m_Color(sf::Color(1,1,1,0))
{}

Light::Light(const Vector3& vec, sf::Color col)
	: m_Position(vec)
	, m_Color(col)
{}

// Setter
Vector3 Light::getLightPosition()
{
	return m_Position;
}

void Light::setLightPosition(Vector3 v1)
{
	m_Position = v1;
}

sf::Color Light::getLightColor()
{
	return m_Color;
}

void Light::setLightColor(sf::Color col)
{
	m_Color = col;
}