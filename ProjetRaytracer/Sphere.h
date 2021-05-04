#ifndef SPHERE_H
#define SPHERE_H

#include <SFML/Graphics.hpp>
#include "Vector3.h"
#include "Ray.h"
#include "Object.h"
//#include "Color.h"

class Sphere : public Object
{
public:
	Sphere();
	Sphere(class Vector3 center, double radius, sf::Color col);
	~Sphere() = default;

	//Getter and Setter
	double getRadius();
	void setRadius(double radius);
	class Vector3 getCenter();
	void setCenter(class Vector3 center);
	sf::Color getColor() override;
	void setSphereColor(sf::Color col);

	double Volume();
	double Aire();
	double Intersect_sphere(const class Ray& r);
	Vector3 getNormalAt(Vector3 point);
	double FindIntersection(const Ray& ray) override;

private:
	double m_radius;
	Vector3 m_center;
	sf::Color m_color;
};

#endif // !SPHERE_H