#include "Plane.h"
#include <math.h>

const double PI = 3.14;

Plane::Plane()
	:m_normal(Vector3(1, 0, 0))
	, m_distance(0)
	, m_color(sf::Color(128, 128, 128, 255))
{}

Plane::Plane(Vector3 normal, double distance, sf::Color col)
	: m_normal(normal)
	, m_distance(distance)
	, m_color(col)
{}

Vector3 Plane::getNormalAt(Vector3 point)
{
	return m_normal;
}

void Plane::setPlaneNormal(Vector3 normal)
{
	m_normal = normal;
}

double Plane::getPlaneDistance()
{
	return m_distance;
}

void Plane::setPlaneDistance(double distance)
{
	m_distance = distance;
}

sf::Color Plane::getColor()
{
	return m_color;
}

void Plane::setPlaneColor(sf::Color col)
{
	m_color = col;
}

double Plane::FindIntersection(const Ray& ray)
{
	Vector3 ray_direction = ray.Direction();

	double a = ray_direction.dotProduct(m_normal);

	if (a == 0)
	{
		// ray is parallel to the plane 
		return -1;
	}
	else
	{
		double b = m_normal.dotProduct(ray.Origin().vectAdd(m_normal.vectMult(m_distance).Negative()));
		return - b / a;
	}
}