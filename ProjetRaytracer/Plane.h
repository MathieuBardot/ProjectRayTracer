#ifndef PLANE_H
#define PLANE_H

#include <SFML/Graphics.hpp>
#include "Vector3.h"
#include "Ray.h"
#include "Object.h"
//#include "Color.h"

class Plane : public Object
{
public:
	Plane();
	Plane(class Vector3 normal, double distance, sf::Color col);
	~Plane() = default;

	//Getter and Setter
	Vector3 getNormalAt(Vector3 point) override;
	void setPlaneNormal(class Vector3 normal);
	double getPlaneDistance();
	void setPlaneDistance(double distance);
	sf::Color getColor() override;
	void setPlaneColor(sf::Color col);

	double FindIntersection(const Ray& ray) override;

private:
	double m_distance;
	Vector3 m_normal;
	sf::Color m_color;
};

#endif // !PLANE_H