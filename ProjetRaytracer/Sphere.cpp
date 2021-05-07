#include "Sphere.h"
#include <math.h>

Sphere::Sphere()
	:m_Center(Vector3(0,0,0))
	,m_Radius(1.0)
	,m_Color(sf::Color(128,128,128,255))
{}

Sphere::Sphere(Vector3 center, double radius, sf::Color col) 
	: m_Center(center)
	, m_Radius(radius) 
	, m_Color(col)
{}

// Getter and Setter
double Sphere::getRadius()
{
	return m_Radius;
}

void Sphere::setRadius(double radius)
{
	m_Radius = radius;
}

Vector3 Sphere::getCenter()
{
	return m_Center;
}

void Sphere::setCenter(Vector3 center)
{
	m_Center = center;
}

sf::Color Sphere::getColor()
{
	return m_Color;
}

void Sphere::setSphereColor(sf::Color col)
{
	m_Color = col;
}

Vector3 Sphere::getNormalAt(Vector3 point)
{
	//normal always point away from the center of a sphere
	Vector3 normal_vect = point.vectAdd(m_Center.Negative()).Normalize();
	return normal_vect;
}

// Method to fin the intersection between the ray and the sphere
double Sphere::FindIntersection(const Ray& ray) 
{
	Vector3 oc = ray.Origin() - m_Center;
	double a = oc.ProduitScalaire(ray.Direction(), ray.Direction());
	double b = 2.0 * oc.ProduitScalaire(oc, ray.Direction());
	double c = oc.ProduitScalaire(oc, oc) - pow(m_Radius, 2);
	double discriminant = pow(b, 2) - 4 * a * c;

	if (discriminant > 0)
	{
		// the ray intersects the sphere 
		// the first root
		double solution1 = ((-b - sqrt(discriminant) / (2*a)));

		if (solution1 > 0)
		{
			// the first root is the smallest positive root
			return solution1;
		}
		else
		{
			// the first root is the smallest positive root
			double solution2 = ((sqrt(discriminant) - b) / (2*a));
			return solution2;
		}
	}
	else
	{
		// the ray missed the sphere
		return -1;
	}
} 