#include "Plane.h"
#include <math.h>

const double PI = 3.14;

Plane::Plane()
	: m_Normal(Vector3(1, 0, 0))
	, m_Distance(0)
	, m_Color(sf::Color(128, 128, 128, 255))
{}

Plane::Plane(Vector3 normal, double distance, sf::Color col)
	: m_Normal(normal)
	, m_Distance(distance)
	, m_Color(col)
{}

// Getter and Setter
Vector3 Plane::getNormalAt(Vector3 point)
{
	return m_Normal;
}

void Plane::setPlaneNormal(Vector3 normal)
{
	m_Normal = normal;
}

double Plane::getPlaneDistance()
{
	return m_Distance;
}

void Plane::setPlaneDistance(double distance)
{
	m_Distance = distance;
}

sf::Color Plane::getColor()
{
	return m_Color;
}

void Plane::setPlaneColor(sf::Color col)
{
	m_Color = col;
}

// Methode to search if ray has intersections with the plane
double Plane::FindIntersection(const Ray& ray)
{
	Vector3 ray_direction = ray.Direction();

	double a = ray_direction.dotProduct(m_Normal);

	if (a == 0)
	{
		// ray is parallel to the plane 
		return -1;
	}
	else
	{
		double b = m_Normal.dotProduct(ray.Origin().vectAdd(m_Normal.vectMult(m_Distance).Negative()));
		return - b / a;
	}
}