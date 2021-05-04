#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vector3.h"
#include "Color.h"
#include "Ray.h"
#include "Camera.h"
#include "Light.h"
#include "Sphere.h"
#include "Object.h"
#include "Plane.h"

int winningObjectIndex(std::vector<double> object_intersections)
{
    // return the index of the winning intersection
    int index_of_minimum_value = 1;

    // prevent unnessary calcul
    if (object_intersections.size() == 0)
    {
        // if there are no intersections
        return -1;
    }
    else if (object_intersections.size() == 1)
    {
        if (object_intersections[0] > 0)
        {
            // if that intersection is greater than zeto then its our index of min value  
            return 0;
        }
        else
        {
            // otherwise the only intersection value is negative
            return -1;
        }
    }
    else
    {
        // otherwise there is more than one intersection
        // first find the max value
        double max = 0;
        for (auto i = 0; i < object_intersections.size(); ++i)
        {
            if (max < object_intersections[i])
                max = object_intersections[i];
        }

        // then starting form the max calue find the min positive value
        if (max > 0)
        {
            // we only want positive intersections
            for (auto index = 0; index < object_intersections.size(); ++index)
            {
                if (object_intersections[index] > 0 && object_intersections[index] <= max)
                {
                    max = object_intersections[index];
                    index_of_minimum_value = index;
                }
            }
            return index_of_minimum_value;
        }
        else
        {
            // all the intersections were negative
            return -1;
        }
    }
}

int main()
{
    // Taille de l'image.
    const int image_width = 640;
    const int image_height = 480;
    const auto aspect_ratio = (double)image_width / (double)image_height;
    sf::RenderWindow window(sf::VideoMode(image_width, image_height), "Projet Raytracer");

    // Création du tableau de pixels.
    auto * pixels = new sf::Uint8[image_width * image_height * 4];

    sf::Texture texture;
    if (!texture.create(image_width, image_height))
        return -1;

    sf::Sprite sprite(texture);
    window.setFramerateLimit(60);

    // Add Camera 
    Vector3 origin(0, 0, 0);

    Vector3 camPosition(3, 1.5, -4);
    Vector3 diff_btw(camPosition.getX() - origin.getX(), 
        camPosition.getY() - origin.getY(), 
        camPosition.getZ() - origin.getZ());
    
    Vector3 camDirection = diff_btw.Negative().Normalize();
    Vector3 camRight = Vector3(0, 1, 0).crossProduct(camDirection).Normalize();
    Vector3 camDown = camRight.crossProduct(camDirection);

    Camera scene_cam(camPosition, camDirection, camRight, camDown);

    // Add Light and Color
    sf::Color white_light = sf::Color::Color(255,255,255,255);
    sf::Color green = sf::Color::Color(128, 255, 128, 177);
    //sf::Color green = sf::Color::Color(128, 255, 128, 255);
    sf::Color gray = sf::Color::Color(128, 128, 128, 255);
    sf::Color black = sf::Color::Color(0, 0, 0, 255);
    sf::Color maroon  = sf::Color::Color(128, 64, 64, 255);

    Vector3 light_position(-7, 10, -10);
    Light scene_light(light_position, white_light);
    //Light scene_light(light_position, sf::Color::White);

    //std::cout << static_cast<int>(green.r) << " / " << green.g << " / " << green.b << " / " << green.a << std::endl;

    // Add scene objects
    Sphere scene_sphere(Vector3(0, 0, 0), 1, green);
    Plane scene_plane(Vector3(0, 10, 0), -1, maroon);
    //Sphere scene_sphere(Vector3(0, 0, 0), 1, sf::Color::Green);
    //Plane scene_plane(Vector3(0, 1, 0), -1, sf::Color::Red);

    std::vector<Object*> scene_objects;
    scene_objects.push_back(dynamic_cast<Object*>(&scene_sphere));
    scene_objects.push_back(dynamic_cast<Object*>(&scene_plane));

    double xamnt, yamnt;
    int currentPosition;

    for (int i = 0; i < image_width; ++i)
    {
        for (int j = 0; j < image_height; ++j)
        {
            currentPosition = j * image_width + i;
            // start with no anti-aliasing
            if (image_width > image_height)
            {
                // the image is wider tan it is tall
                xamnt = ((i + 0.5) / image_width) * aspect_ratio - (((image_width - image_height) / (double)image_height) / 2);
                yamnt = ((image_height - j) + 0.5) / image_height;
            }
            else if (image_height > image_width)
            {
                // the image is taller tan it is wide
                xamnt = (i + 0.5) / image_width;
                yamnt = (((image_height - j) + 0.5) / image_height) / aspect_ratio - (((image_height - image_width) / (double)image_width) / 2);
            }
            else
            {
                // the image is square
                xamnt = (i + 0.5) / image_width;
                yamnt = ((image_height - j)+0.5)/image_height;
            }

            Vector3 camera_ray_origin = scene_cam.CameraPosition();
            Vector3 camera_ray_direction = camDirection.vectAdd(camRight.vectMult(xamnt - 0.5).vectAdd(camDown.vectMult(yamnt - 0.5))).Normalize();

            Ray camera_ray(camera_ray_origin, camera_ray_direction);

            std::vector<double> intersections;

            for (auto index = 0; index < scene_objects.size(); ++index)
            {
                intersections.push_back(scene_objects[index]->FindIntersection(camera_ray));
            }

            int index_of_winning_object = winningObjectIndex(intersections);

            //std::cout << index_of_winning_object;

            if (index_of_winning_object == -1)
            {
                // set the backgrounf Black
                pixels[4*currentPosition] = 0;
                pixels[4*currentPosition + 1] = 0;
                pixels[4*currentPosition + 2] = 0;
                pixels[4*currentPosition + 3] = 255;
            }
            else
            {
                // index corresponds to an object in our scene
                sf::Color this_color = scene_objects[index_of_winning_object]->getColor();

                /*std::cout << "Couleur obtenue : " 
                    << static_cast<int>(this_color.r) << " / " 
                    << static_cast<int>(this_color.g) << " / " 
                    << static_cast<int>(this_color.b) << std::endl;*/

                pixels[4*currentPosition] = static_cast<int>(this_color.r);
                pixels[4*currentPosition+1] = static_cast<int>(this_color.g);
                pixels[4*currentPosition+2] = static_cast<int>(this_color.b);
                pixels[4*currentPosition + 3] = static_cast<int>(this_color.a);
            }
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