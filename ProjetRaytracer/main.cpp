#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vector3.h"
#include "Color.h"
#include "Ray.h"
#include "Camera.h"
#include "Light.h"
#include "Sphere.h"
#include "Plane.h"

/************ Method to define the index intersection between ray and objects *************************/
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

/**************** Method to define the shadow generate by object position ***********************/
sf::Color getColorAt(Vector3 intersection_position, Vector3 intersections_ray_direction, std::vector<Object*>scene_objects, int index_of_winning_object, std::vector<Source*> light_sources, double accuracy, double ambientLight)
{
    sf::Color winning_object_color = scene_objects[index_of_winning_object]->getColor();
    Vector3 winning_object_normal = scene_objects[index_of_winning_object]->getNormalAt(intersection_position);
    
    if (static_cast<int>(winning_object_color.a) == 255) // winning_object_color.a == 2
    {
        // checkered/tile floor pattern
        int square = (int)floor(intersection_position.getX()) + (int)floor(intersection_position.getZ());

        if ((square % 2) == 0)
        {
            // black tile
            winning_object_color.r = 0;
            winning_object_color.g = 0;
            winning_object_color.b = 0;
        }
        else
        {
            winning_object_color.r = 255;
            winning_object_color.g = 255;
            winning_object_color.b = 255;
        }
    }
    
    sf::Color final_color (static_cast<double>(winning_object_color.r) * ambientLight, 
        static_cast<double>(winning_object_color.g) * ambientLight,
        static_cast<double>(winning_object_color.b) * ambientLight,
        static_cast<double>(winning_object_color.a));

    if (static_cast<int>(winning_object_color.a) > 0 && static_cast<int>(winning_object_color.a) <= 128)
    {
        // reflection from objects with tranparence intensity
        double dot1 = winning_object_normal.dotProduct(intersections_ray_direction.Negative());
        Vector3 scalar1 = winning_object_normal.vectMult(dot1);
        Vector3 add1 = scalar1.vectAdd(intersections_ray_direction);
        Vector3 scalar2 = add1.vectMult(2);
        Vector3 add2 = intersections_ray_direction.Negative().vectAdd(scalar2);
        Vector3 reflection_direction = add2.Normalize();

        Ray reflection_ray(intersection_position, reflection_direction);
         
        // determine what the ray intersects with first
        std::vector<double> reflection_intersections;

        for (auto reflection_index = 0; reflection_index < scene_objects.size(); ++reflection_index)
            reflection_intersections.push_back(scene_objects[reflection_index]->FindIntersection(reflection_ray));

        int index_of_winning_object_with_reflection = winningObjectIndex(reflection_intersections);

        if (index_of_winning_object_with_reflection != -1)
        {
            // reflection ray missed everything else
            if (reflection_intersections[index_of_winning_object_with_reflection] > accuracy)
            {
                // determine the position and direction at the point of intersection with the reflection
                // the ray only affects the color if it reflected off something
                Vector3 reflection_intersection_position = intersection_position.vectAdd(reflection_direction.vectMult(reflection_intersections[index_of_winning_object_with_reflection]));
                Vector3 reflection_intersection_ray_direction = reflection_direction;
            
                sf::Color reflection_intersection_color = getColorAt(reflection_intersection_position, reflection_intersection_ray_direction, scene_objects, index_of_winning_object_with_reflection, light_sources, accuracy, ambientLight);

                sf::Color temp (static_cast<int>(reflection_intersection_color.r) * (winning_object_color.a),
                    static_cast<int>(reflection_intersection_color.g) * (winning_object_color.a),
                    static_cast<int>(reflection_intersection_color.b) * (winning_object_color.a),
                    static_cast<int>(reflection_intersection_color.a));
                final_color = final_color + temp;
            }
        }
    }

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
                secondary_intersections.push_back(scene_objects[object_index]->FindIntersection(shadow_ray));

            for (auto c = 0; c < secondary_intersections.size(); ++c)
            {
                if (secondary_intersections[c] > accuracy)
                {
                    if (secondary_intersections[c] <= distance_to_light_magnitude)
                        shadowed = true;
                }
                break;
            }

            if (shadowed == false)
            {
                sf::Color temp = light_sources[light_index]->getLightColor();
                temp = sf::Color(static_cast<float>(temp.r) * cosine_angle,
                    static_cast<float>(temp.g) * cosine_angle,
                    static_cast<float>(temp.b) * cosine_angle,
                    static_cast<float>(temp.a));
                final_color = final_color + winning_object_color * temp;

                // transparence between 0 - 128
                if (static_cast<int>(winning_object_color.a) > 0 && static_cast<int>(winning_object_color.a) <= 128)
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
    /**************** Define size image and some parameters *******************/
    const int image_width = 640;
    const int image_height = 480;
    sf::RenderWindow window(sf::VideoMode(image_width, image_height), "Projet Raytracer");

    const auto aspect_ratio = (double)image_width / (double)image_height;
    double ambientLight = 0.2;
    double accuracy = 0.000001;
    const int aadepth = 1;
    double aathreshold = 0.1;

    //sf::Clock t1;

    // Création du tableau de pixels.
    auto* pixels = new sf::Uint8[image_width * image_height * 4];

    sf::Texture texture;
    if (!texture.create(image_width, image_height))
        return -1;

    sf::Sprite sprite(texture);
    window.setFramerateLimit(60);

    /************************** Add Camera ***************************/
    Vector3 origin(0, 0, 0);

    Vector3 camPosition(3, 1.5, -4);
    Vector3 diff_btw(camPosition - origin);

    Vector3 camDirection = diff_btw.Negative().Normalize();
    Vector3 camRight = Vector3(0, -1, 0).crossProduct(camDirection).Normalize();
    Vector3 camDown = camRight.crossProduct(camDirection);

    Camera scene_cam(camPosition, camDirection, camRight, camDown);

    /*********************** Add Light and Color *************************/
    sf::Color white_light(255,255,255,255);
    sf::Color green(128, 255, 128, 177);
    sf::Color red (255, 0, 0, 177);
    sf::Color gray (128, 128, 128, 255);
    sf::Color black (0, 0, 0, 255);
    sf::Color maroon (128, 64, 64, 255);
    sf::Color tile_floor(128, 128, 128, 255);

    // Define the position and the color of Light on the image 
    //Vector3 light_position(-7, 10, -10); // basic position 
    Vector3 light_position(10, 15, 30);
    Light scene_light(light_position, white_light);

    std::vector<Source*> light_sources;
    light_sources.push_back(dynamic_cast<Source*>(&scene_light));

    /*********************** Add scene objects *****************************
    ******** Initiate position, radius and color of sphere *****************
    **** Initiate position, distance to the plane and color of plane *******/
    //Sphere scene_sphere(Vector3(1, 1.3, -1.3), 1, green);
    Sphere scene_sphere(Vector3(0, 0, 0), 1, green);
    Plane scene_plane(Vector3(0, 3.2, 0), -1, tile_floor); 
    //Sphere scene_sphere_ground(Vector3(0, -10.5, -1), 11, maroon);
    Sphere scene_sphere_test(Vector3(-0.8, 0, -1.5), 0.5, red);

    std::vector<Object*> scene_objects;
    scene_objects.push_back(dynamic_cast<Object*>(&scene_sphere));
    scene_objects.push_back(dynamic_cast<Object*>(&scene_sphere_test));
    scene_objects.push_back(dynamic_cast<Object*>(&scene_plane));
    //scene_objects.push_back(dynamic_cast<Object*>(&scene_sphere_ground));

    int currentPosition;
    double xamnt, yamnt;
    // start with a blank pixel
    double tempRed[aadepth * aadepth];
    double tempGreen[aadepth * aadepth];
    double tempBlue[aadepth * aadepth];

    for (int i = 0; i < image_width; ++i)
    {
        for (int j = 0; j < image_height; ++j)
        {
            currentPosition = j * image_width + i;

            for (auto aax = 0; aax < aadepth; ++aax)
            {
                for (auto aay = 0; aay < aadepth; ++ aay)
                {
                    int aa_index = aay * aadepth + aax;

                    srand(time(0));
                    
                    // create the ray from the camera to this pixel
                    if (aadepth == 1)
                    {
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
                            yamnt = ((image_height - j) + 0.5) / image_height;
                        }
                    }
                    else
                    {
                        // anti-aliasing
                        if (image_width > image_height)
                        {
                            // the image is wider tan it is tall
                            xamnt = ((i + (double)aax/((double)aadepth-1)) / image_width) * aspect_ratio - (((image_width - image_height) / (double)image_height) / 2);
                            yamnt = ((image_height - j) + (double)aax / ((double)aadepth - 1)) / image_height;
                        }
                        else if (image_height > image_width)
                        {
                            // the image is taller tan it is wide
                            xamnt = (i + (double)aax / ((double)aadepth - 1)) / image_width;
                            yamnt = (((image_height - j) + (double)aax / ((double)aadepth - 1)) / image_height) / aspect_ratio - (((image_height - image_width) / (double)image_width) / 2);
                        }
                        else
                        {
                            // the image is square
                            xamnt = (i + (double)aax / ((double)aadepth - 1)) / image_width;
                            yamnt = ((image_height - j) + (double)aax / ((double)aadepth - 1)) / image_height;
                        }
                    }

                    Vector3 camera_ray_origin = scene_cam.CameraPosition();
                    Vector3 camera_ray_direction = camDirection.vectAdd(camRight.vectMult(xamnt - 0.5).vectAdd(camDown.vectMult(yamnt - 0.5))).Normalize();

                    Ray camera_ray(camera_ray_origin, camera_ray_direction);

                    std::vector<double> intersections;

                    for (auto index = 0; index < scene_objects.size(); ++index)
                        intersections.push_back(scene_objects[index]->FindIntersection(camera_ray));

                    int index_of_winning_object = winningObjectIndex(intersections);

                    /******************* Define value of the pixels on the image *********************************/
                    if (index_of_winning_object == -1)
                    {
                        // set the backgrounf Black
                        //tempRed[aa_index] = 0;
                        //tempGreen[aa_index] = 0;
                        //tempBlue[aa_index] = 0;
                        pixels[4 * currentPosition] = 0;
                        pixels[4 * currentPosition + 1] = 0;
                        pixels[4 * currentPosition + 2] = 0;
                        pixels[4 * currentPosition + 3] = 255;
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
                            sf::Color intersection_color = getColorAt(intersection_position, intersections_ray_direction, scene_objects, index_of_winning_object, light_sources, accuracy, ambientLight);

                            //tempRed[aa_index] = static_cast<int>(intersection_color.r);
                            //tempGreen[aa_index] = static_cast<int>(intersection_color.g);
                            //tempBlue[aa_index] = static_cast<int>(intersection_color.b);
                            pixels[4 * currentPosition] = static_cast<int>(intersection_color.r);
                            pixels[4 * currentPosition + 1] = static_cast<int>(intersection_color.g);
                            pixels[4 * currentPosition + 2] = static_cast<int>(intersection_color.b);
                            pixels[4 * currentPosition + 3] = static_cast<int>(intersection_color.a);
                        }
                    }
                }
            }

            //average the pixel color;
            /*double totalRed = 0;
            double totalGreen = 0;
            double totalBlue = 0;

            for (auto iRed = 0; iRed < aadepth * aadepth; ++iRed)
                totalRed = totalRed + tempRed[iRed];

            for (auto iGreen = 0; iGreen < aadepth * aadepth; ++iGreen)
                totalGreen = totalGreen + tempGreen[iGreen];

            for (auto iBlue = 0; iBlue < aadepth * aadepth; ++iBlue)
                totalBlue = totalBlue + tempBlue[iBlue];

            double avgRed = totalRed / (aadepth * aadepth);
            double avgGreen = totalGreen / (aadepth * aadepth);
            double avgBlue = totalBlue / (aadepth * aadepth);

            pixels[4 * currentPosition] = avgRed;
            pixels[4 * currentPosition + 1] = avgGreen;
            pixels[4 * currentPosition + 2] = avgBlue;*/
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

    delete pixels;
    
    /*sf::Clock t2;
    sf::Time elapsed1 = t1.getElapsedTime();
    sf::Time elapsed2 = t2.getElapsedTime();

    sf::Time diff = elapsed1 - elapsed2;
    std::cout << "Temps d'execution : " << diff.asSeconds() << " seconds " << std::endl;
    */
    return 0;
}