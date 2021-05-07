#ifndef PLANE_H
#define PLANE_H

#include <SFML/Graphics/Color.hpp>
#include "Vector3.h"
#include "Ray.h"
#include "Object.h"

class Plane : public Object
{
public:
	Plane();
	Plane(Vector3 normal, double distance, sf::Color col);
	~Plane() = default;

	//Getter and Setter
	Vector3 getNormalAt(Vector3 point) override;
	void setPlaneNormal(Vector3 normal);
	double getPlaneDistance();
	void setPlaneDistance(double distance);
	sf::Color getColor() override;
	void setPlaneColor(sf::Color col);

	double FindIntersection(const Ray& ray) override;

private:
	double m_Distance;
	Vector3 m_Normal;
	sf::Color m_Color;
};

#endif // !PLANE_H