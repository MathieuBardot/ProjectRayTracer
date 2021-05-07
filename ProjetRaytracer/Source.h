#ifndef SOURCE_H
#define SOURCE_H

#include <SFML/Graphics/Color.hpp>
#include "Vector3.h"

class Source
{
public:
	Source() = default;

	virtual Vector3 getLightPosition() { return Vector3(0, 0, 0); };
	
	virtual sf::Color getLightColor() { return sf::Color(255, 255, 255, 0); };

};

#endif // !SOURCE_H