#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

class Ray
{
public:
	Ray();
	Ray(const Vector3& a, const Vector3& b);

	//Gette and Setter
	Vector3 getA();
	void setA(Vector3 v1);
	Vector3 getB();
	void setB(Vector3 v1);

	Vector3 origin() const;
	Vector3 direction() const;
	Vector3 point_at_parameter(float t) const;

private:
	Vector3 m_A;
	Vector3 m_B;
};

#endif // !RAY_H