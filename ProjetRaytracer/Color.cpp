#include "Color.h"

Color::Color()
    : m_Red(0)
    , m_Green(0)
    , m_Blue(0)
    , m_Transparence(0)
{}

Color::Color(const double rouge, const double vert, const double bleu, const double transparence)
    : m_Red(rouge)
    , m_Green(vert)
    , m_Blue(bleu)
    , m_Transparence(transparence)
{}

Color::~Color() {}

// Getter and Setter
double Color::getRed()
{
    return m_Red;
}

void Color::setRed(double r)
{
    m_Red = r;
}

double Color::getGreen()
{
    return m_Green;
}

void Color::setGreen(double g)
{
    m_Green = g;
}

double Color::getBlue()
{
    return m_Blue;
}

void Color::setBlue(double b)
{
    m_Blue = b;
}

double Color::getTransparence()
{
    return m_Transparence;
}

void Color::setTransparence(double transparence)
{
    m_Transparence = transparence;
}

// Fonction qui permet de "vider" l'array, ici j'initialise tous les pixels à (255, 0, 0, 255), donc rouge sans transparence.
void Color::emptyArray(sf::Uint8* pixels, int width, int height)
{
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            pixels[4 * (j * width + i)] = 255;
            pixels[4 * (j * width + i) + 1] = 0;
            pixels[4 * (j * width + i) + 2] = 0;
            pixels[4 * (j * width + i) + 3] = 255;
        }
    }
}

// Fonction qui permet de change un pixel, en lui affectant une couleur RGB, on lui laisse sa transparence à 255 (donc sans transparence).
void Color::writeColor(sf::Uint8* pixels, int x, int y, int width, Vector3 color)
{
    pixels[4 * (y * width + x)] = static_cast<int>(255.99 * color.getX());
    pixels[4 * (y * width + x) + 1] = static_cast<int>(255.99 * color.getY());
    pixels[4 * (y * width + x) + 2] = static_cast<int>(255.99 * color.getZ());
    pixels[4 * (y * width + x) + 3] = 255;
}