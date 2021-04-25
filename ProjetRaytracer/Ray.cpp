#include "Ray.h"

Ray::Ray() {}

Ray::Ray(const Vector3& a, const Vector3& b)
{
	m_A = a;
	m_B = b;
}

// Getter and Setter
Vector3 Ray::getA()
{
	return m_A;
}

void Ray::setA(Vector3 v1)
{
	m_A = v1;
}

Vector3 Ray::getB()
{
	return m_B;
}

void Ray::setB(Vector3 v1)
{
	m_B = v1;
}

Vector3 Ray::origin() const
{
	return m_A;
}

Vector3 Ray::direction() const
{
	return m_B;
}

Vector3 Ray::point_at_parameter(float t) const
{
	return m_A + t * m_B;
}