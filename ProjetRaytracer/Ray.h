#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

class Ray
{
public:
	Ray();
	Ray(const Vector3& a, const Vector3& b);

	//Getter and Setter
	void setOrigin(Vector3 v1);
	void setDirection(Vector3 v1);

	Vector3 Origin() const;
	Vector3 Direction() const;
	Vector3 point_at_parameter(double t) const;

private:
	Vector3 m_Origin;
	Vector3 m_Direction;
};

#endif // !RAY_H