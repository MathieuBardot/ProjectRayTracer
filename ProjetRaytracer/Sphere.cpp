#include "Sphere.h"
#include <math.h>
#include "Vector3.h"
#include "Ray.h"

const float PI = 3.14;

Sphere::Sphere(Vector3 center, float radius) : m_center(center), m_radius(radius) {}

float Sphere::getRadius()
{
	return m_radius;
}

void Sphere::setRadius(float rayon)
{
	m_radius = rayon;
}

Vector3 Sphere::getCenter()
{
	return m_center;
}

void Sphere::setCenter(Vector3 center)
{
	m_center = center;
}

float Sphere::Volume()
{
	return 4.0 / 3.0 * PI * pow(m_radius, 3);
}
float Sphere::Aire()
{
	return 4.0 * PI * pow(m_radius, 2);
}

/*float Sphere::Intersect_sphere(const Ray& r)
{
	Vector3 oc = r.origin() - m_center;
	float a = oc.ProduitScalaire(r.direction(), r.direction());
	float b = 2.0 * oc.ProduitScalaire(oc, r.direction());
	float c = oc.ProduitScalaire(oc, oc) - pow(m_radius,2);
	float discriminant = pow(b,2) - 4 * a * c;
	if (discriminant < 0)
		return -1.0;
	else
		return (-b - sqrt(discriminant)) / (2.0 * a);
}*/

bool Sphere::Intersect_sphere(const Ray& r)
{
	Vector3 oc = r.origin() - m_center;
	float a = oc.ProduitScalaire(r.direction(), r.direction());
	float b = 2.0 * oc.ProduitScalaire(oc, r.direction());
	float c = oc.ProduitScalaire(oc, oc) - pow(m_radius, 2);
	float discriminant = pow(b, 2) - 4 * a * c;
	return (discriminant > 0);
}

Vector3 Sphere::color(const Ray& r)
{
	/*float t = Intersect_sphere(r);
	if (t > 0.0)
	{
		Vector3 N;
		N.unit_vector(r.point_at_parameter(t) - Vector3(0, 0, -1));
		return 0.5 * Vector3(N.getX() + 1, N.getY() + 1, N.getZ() + 1);
	}*/
	if (Intersect_sphere(r))
		return Vector3(1, 0, 0);
	Vector3 unit_direction;
	unit_direction.unit_vector(r.direction());
	float t = 0.5 * (unit_direction.getY() + 1.0);
	return (1.0 - t) * Vector3(1.0, 1.0, 1.0) + t * Vector3(0.5, 0.7, 1.0);
}