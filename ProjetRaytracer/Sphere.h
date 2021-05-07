#ifndef SPHERE_H
#define SPHERE_H

#include <SFML/Graphics/Color.hpp>
#include "Vector3.h"
#include "Ray.h"
#include "Object.h"

class Sphere : public Object
{
public:
	Sphere();
	Sphere(Vector3 center, double radius, sf::Color col);
	~Sphere() = default;

	//Getter and Setter
	double getRadius();
	void setRadius(double radius);
	Vector3 getCenter();
	void setCenter(Vector3 center);
	sf::Color getColor() override;
	void setSphereColor(sf::Color col);

	Vector3 getNormalAt(Vector3 point) override;
	double FindIntersection(const Ray& ray) override;

private:
	double m_Radius;
	Vector3 m_Center;
	sf::Color m_Color;
};

#endif // !SPHERE_H