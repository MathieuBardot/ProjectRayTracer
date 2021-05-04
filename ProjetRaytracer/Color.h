#ifndef COLOR_H
#define COLOR_H

#include <SFML/Graphics.hpp>
#include "Vector3.h"

class Color
{
public:
	Color();
	Color(const double rouge, const double vert, const double bleu, const double transparence);
	~Color();

	// Getter and Setter
	double getRed();
	void setRed(double r);
	double getGreen();
	void setGreen(double g);
	double getBlue();
	void setBlue(double b);
	double getTransparence();
	void setTransparence(double tranparence);

	void emptyArray(sf::Uint8* pixels, int width, int height);
	void writeColor(sf::Uint8* pixels, int x, int y, int width, Vector3 color);

private:
	double m_Red;
	double m_Green;
	double m_Blue;
	double m_Transparence;
};

#endif // !COLOR_H


