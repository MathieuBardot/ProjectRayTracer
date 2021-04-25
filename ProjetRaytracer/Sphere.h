#ifndef SPHERE_H
#define SPHERE_H

#include "Vector3.h"

class Sphere
{
public:
	Sphere() = default;
	Sphere(class Vector3 center, float radius);
	~Sphere() = default;

	//Getter and Setter
	float getRadius();
	void setRadius(float radius);
	class Vector3 getCenter();
	void setCenter(class Vector3 center);

	float Volume();
	float Aire();
	//float Intersect_sphere(const class Ray &r);
	bool Intersect_sphere(const class Ray& r);
	class Vector3 color(const class Ray& r);

private:
	float m_radius;
	Vector3 m_center;
};

#endif // !SPHERE_H