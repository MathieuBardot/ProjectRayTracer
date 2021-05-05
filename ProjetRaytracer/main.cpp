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
#include "Source.h"

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

sf::Color getColorAt(Vector3 intersection_position, Vector3 intersections_ray_direction, std::vector<Object*>scene_objects, int index_of_winning_object, std::vector<Source*> light_sources, double accuracy, double ambientLight)
{
    sf::Color winning_object_color = scene_objects[index_of_winning_object]->getColor();
    Vector3 winning_object_normal = scene_objects[index_of_winning_object]->getNormalAt(intersection_position);
    sf::Color final_color (static_cast<double>(winning_object_color.r) * ambientLight, 
        static_cast<double>(winning_object_color.g) * ambientLight,
        static_cast<double>(winning_object_color.b) * ambientLight,
        static_cast<double>(winning_object_color.a));

    for (auto light_index = 0; light_index < light_sources.size(); ++light_index)
    {
        Vector3 light_direction = light_sources[light_index]->getLightPosition().vectAdd(intersection_position.Negative()).Normalize();
       
        float cosine_angle = winning_object_normal.dotProduct(light_direction);

        if (cosine_angle > 0)
        {
            // test for shadows
            bool shadowed = false;

            Vector3 distance_to_light = light_sources[light_index]->getLightPosition().vectAdd(intersection_position.Negative()).Normalize();
            float distance_to_light_magnitude = distance_to_light.Magnitude();

            Ray shadow_ray(intersection_position,light_sources[light_index]->getLightPosition().vectAdd(intersection_position.Negative()).Normalize());
        
            std::vector<double> secondary_intersections;

            for (auto object_index = 0; object_index < scene_objects.size() && shadowed == false; ++object_index)
            {
                secondary_intersections.push_back(scene_objects[object_index]->FindIntersection(shadow_ray));
            }

            for (auto c = 0; c < secondary_intersections.size(); ++c)
            {
                if (secondary_intersections[c] > accuracy)
                {
                    if (secondary_intersections[c] <= distance_to_light_magnitude)
                    {
                        shadowed = true;
                    }
                }
                break;
            }

            if (shadowed == false)
            {
                // see part 7 at 1h07m28s
                sf::Color temp = light_sources[light_index]->getLightColor();
                temp = sf::Color(static_cast<float>(temp.r) * cosine_angle,
                    static_cast<float>(temp.g) * cosine_angle,
                    static_cast<float>(temp.b) * cosine_angle,
                    static_cast<float>(temp.a));
                final_color = final_color + winning_object_color * temp;

                // transparence betwenn 0 - 255
                if (static_cast<int>(winning_object_color.a) > 0 && static_cast<int>(winning_object_color.a) <= 255)
                {
                    double dot1 = winning_object_normal.dotProduct(intersections_ray_direction.Negative());
                    Vector3 scalar1 = winning_object_normal.vectMult(dot1);
                    Vector3 add1 = scalar1.vectAdd(intersections_ray_direction);
                    Vector3 scalar2 = add1.vectMult(2);
                    Vector3 add2 = intersections_ray_direction.Negative().vectAdd(scalar2);
                    Vector3 reflection_direction = add2.Normalize();

                    double transparence = reflection_direction.dotProduct(light_direction);
                    
                    if (transparence > 0)
                    {
                        transparence = std::pow(transparence, 10);
                        sf::Color temp1 = light_sources[light_index]->getLightColor();
                        temp1 = sf::Color(static_cast<int>(temp1.r) * (transparence * static_cast<int>(winning_object_color.a)),
                            static_cast<int>(temp1.g) * (transparence * static_cast<int>(winning_object_color.a)),
                            static_cast<int>(temp1.b) * (transparence * static_cast<int>(winning_object_color.a)),
                            static_cast<double>(temp1.a));
                        final_color = final_color + temp1;
                    }
                }
            }
        }
    }
    return final_color;
}

int main()
{
    // Taille de l'image.
    const int image_width = 640;
    const int image_height = 480;
    sf::RenderWindow window(sf::VideoMode(image_width, image_height), "Projet Raytracer");

    const auto aspect_ratio = (double)image_width / (double)image_height;
    double ambientLight = 0.2;
    double accuracy = 0.000001;

    // Création du tableau de pixels.
    auto* pixels = new sf::Uint8[image_width * image_height * 4];

    sf::Texture texture;
    if (!texture.create(image_width, image_height))
        return -1;

    sf::Sprite sprite(texture);
    window.setFramerateLimit(60);

    // Add Camera 
    Vector3 origin(0, 0, 0);

    Vector3 camPosition(3, 1.5, -4);
    Vector3 diff_btw(camPosition - origin);

    Vector3 camDirection = diff_btw.Negative().Normalize();
    Vector3 camRight = Vector3(0, -1, 0).crossProduct(camDirection).Normalize();
    Vector3 camDown = camRight.crossProduct(camDirection);

    Camera scene_cam(camPosition, camDirection, camRight, camDown);

    // Add Light and Color
    sf::Color white_light = sf::Color::Color(255,255,255,255);
    sf::Color green = sf::Color::Color(128, 255, 128, 177);
    sf::Color red = sf::Color::Color(255, 0, 0, 177);
    sf::Color gray = sf::Color::Color(128, 128, 128, 255);
    sf::Color black = sf::Color::Color(0, 0, 0, 255);
    sf::Color maroon  = sf::Color::Color(128, 64, 64, 255);

    //Vector3 light_position(-7, 10, -10);
    Vector3 light_position(10, 20, 25);
    Light scene_light(light_position, white_light);

    std::vector<Source*> light_sources;
    light_sources.push_back(dynamic_cast<Source*>(&scene_light));

    // Add scene objects
    Sphere scene_sphere(Vector3(0, 0, 0), 1, green);
    //Sphere scene_sphere_ground(Vector3(-5, -10, 5), 10, maroon);
    //Sphere scene_sphere_test(Vector3(1, -0.5, 0), 0.5, red);
    Plane scene_plane(Vector3(0, 1, 0), -10, maroon);

    std::vector<Object*> scene_objects;
    scene_objects.push_back(dynamic_cast<Object*>(&scene_sphere));
    //scene_objects.push_back(dynamic_cast<Object*>(&scene_sphere_ground));
    //scene_objects.push_back(dynamic_cast<Object*>(&scene_sphere_test));
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
                if (intersections[index_of_winning_object] > accuracy)
                {
                    // determine the position and direction vectors at the point of intersections
                    Vector3 intersection_position = camera_ray_origin.vectAdd(camera_ray_direction.vectMult(intersections[index_of_winning_object]));
                    Vector3 intersections_ray_direction = camera_ray_direction;

                    //sf::Color intersection_color = scene_objects[index_of_winning_object]->getColor();
                    sf::Color intersection_color = getColorAt(intersection_position,intersections_ray_direction, scene_objects, index_of_winning_object, light_sources, accuracy, ambientLight);

                    pixels[4 * currentPosition] = static_cast<int>(intersection_color.r);
                    pixels[4 * currentPosition + 1] = static_cast<int>(intersection_color.g);
                    pixels[4 * currentPosition + 2] = static_cast<int>(intersection_color.b);
                    pixels[4 * currentPosition + 3] = static_cast<int>(intersection_color.a);
                }
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