#include "Ray.h"

Ray::Ray() 
{
	m_Origin = Vector3(0, 0, 0);
	m_Direction = Vector3(1, 0, 0);
}

Ray::Ray(const Vector3& a, const Vector3& b)
	: m_Origin(a)
	, m_Direction(b)
{}

// Setter
void Ray::setOrigin(Vector3 v1)
{
	m_Origin = v1;
}

void Ray::setDirection(Vector3 v1)
{
	m_Direction = v1;
}

Vector3 Ray::Origin() const
{
	return m_Origin;
}

Vector3 Ray::Direction() const
{
	return m_Direction;
}

Vector3 Ray::point_at_parameter(double t) const
{
	return m_Origin + t * m_Direction;
}