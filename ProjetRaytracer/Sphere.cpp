#include "Sphere.h"
#include <math.h>

const double PI = 3.14;

Sphere::Sphere()
	:m_center(Vector3(0,0,0))
	,m_radius(1.0)
	,m_color(sf::Color(128,128,128,255))
{}

Sphere::Sphere(Vector3 center, double radius, sf::Color col) 
	: m_center(center)
	, m_radius(radius) 
	, m_color(col)
{}

double Sphere::getRadius()
{
	return m_radius;
}

void Sphere::setRadius(double radius)
{
	m_radius = radius;
}

Vector3 Sphere::getCenter()
{
	return m_center;
}

void Sphere::setCenter(Vector3 center)
{
	m_center = center;
}

sf::Color Sphere::getColor()
{
	return m_color;
}

void Sphere::setSphereColor(sf::Color col)
{
	m_color = col;
}

double Sphere::Volume()
{
	return 4.0 / 3.0 * PI * pow(m_radius, 3);
}
double Sphere::Aire()
{
	return 4.0 * PI * pow(m_radius, 2);
}

double Sphere::Intersect_sphere(const Ray& r)
{
	Vector3 oc = r.Origin() - m_center;
	double a = oc.ProduitScalaire(r.Direction(), r.Direction());
	double b = 2.0 * oc.ProduitScalaire(oc, r.Direction());
	double c = oc.ProduitScalaire(oc, oc) - pow(m_radius,2);
	double discriminant = pow(b,2) - 4 * a * c;
	if (discriminant < 0)
		return -1.0;
	else
		return (-b - sqrt(discriminant)) / (2.0 * a);
}

Vector3 Sphere::getNormalAt(Vector3 point)
{
	//normal always point away from the center of a sphere
	Vector3 normal_vect = point.vectAdd(m_center.Negative()).Normalize();
	return normal_vect;
}

double Sphere::FindIntersection(const Ray& ray) 
{
	Vector3 oc = ray.Origin() - m_center;
	double a = oc.ProduitScalaire(ray.Direction(), ray.Direction());
	double b = 2.0 * oc.ProduitScalaire(oc, ray.Direction());
	double c = oc.ProduitScalaire(oc, oc) - std::pow(m_radius, 2);
	double discriminant = std::pow(b, 2) - 4 * a * c;

	if (discriminant > 0)
	{
		// the ray intersects the sphere 

		//the first root
		double solution1 = ((-b - sqrt(discriminant) / (2*a)));

		if (solution1 > 0)
		{
			//the first root is the smallest positive root
			return solution1;
		}
		else
		{
			//the first root is the smallest positive root
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