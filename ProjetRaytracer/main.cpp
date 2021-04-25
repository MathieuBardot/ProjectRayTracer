#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vector3.h"
#include "Ray.h"
#include "Sphere.h"

// Fonction qui permet de "vider" l'array, ici j'initialise tous les pixels à (255, 0, 0, 255), donc rouge sans transparence.
static void emptyArray(sf::Uint8* pixels, int width, int height)
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
static void writeColor(sf::Uint8* pixels, int x, int y, int width, Vector3 color)
{
    pixels[4 * (y * width + x)] = static_cast<int>(255.99*color.getX());
    pixels[4 * (y * width + x) + 1] = static_cast<int>(255.99 * color.getY());
    pixels[4 * (y * width + x) + 2] = static_cast<int>(255.99 * color.getZ());
    pixels[4 * (y * width + x) + 3] = 255;
}

int main()
{
    // Taille de l'image.
    const int image_width = 800;
    const int image_height = 400;
    sf::RenderWindow window(sf::VideoMode(image_width, image_height), "Projet Raytracer");

    // On créé le tableau de pixels.
    auto* pixels = new sf::Uint8[image_width * image_height * 4];

    // On le "vide", mais ici on rend tous les pixels en rouge.
    emptyArray(pixels, image_width, image_height);

    sf::Texture texture;
    if (!texture.create(image_width, image_height))
        return -1;

    sf::Sprite sprite(texture);
    window.setFramerateLimit(60);

    Vector3 origin = Vector3(0, 0, 0);
    Vector3 horizontal = Vector3(4, 0 , 0);
    Vector3 vertical = Vector3(0, 2, 0);
    Vector3 lower_left_corner(-2.0, -1.0, -1.0);

    // Add Sphere
    Sphere s (Vector3(0,0,-1), 0.5);

    for (auto i = 0; i < image_height; i++)
    {
        for (auto j = 0; j < image_width; j++)
        {
            auto u = double(j) / (image_width - 1);
            auto v = double(i) / (image_height - 1);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            Vector3 pixels_color = s.color(r);
            writeColor(pixels, j, i, image_width, pixels_color);
        }
    }

    texture.update(pixels);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}