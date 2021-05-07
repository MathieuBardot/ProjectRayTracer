#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics/Color.hpp>
#include "Ray.h"
#include "Vector3.h"

class Object
{
public:
	Object() = default;
	~Object() = default;

	virtual sf::Color getColor() { return sf::Color(0, 0, 0, 255); };

	virtual Vector3 getNormalAt(Vector3 point) 
	{ 
		return Vector3(0, 0, 0); 
	};

	virtual double FindIntersection(const Ray& ray) { return 0; };

};

#endif // !OBJECT_H