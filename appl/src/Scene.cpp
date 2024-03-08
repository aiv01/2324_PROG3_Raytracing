#include "Scene.h"

//#define _USE_MATH_DEFINES
//#include <cmath>
//M_PI

#include <numbers>
#include <cmath>
#include "Vector3.h"
#include "Ray.h"
#include "Color.h"
#include "Raytracer.h"

Scene::Scene(int screen_width, int screen_height, SDL_Renderer* r) 
{
   width = screen_width;
   height = screen_height;
   renderer = r;

   Sphere sphere01{Vector3{0, 0, -5}, 2.f};
   spheres.push_back(sphere01);
}

Scene::~Scene() 
{

}

void Scene::Update(float delta_time) 
{   
    static float aspect_ratio = (float)width / (float)height;

    static float vertFovDegrees = 60.f;
    static float halfFovRads = (vertFovDegrees * 0.5f) * std::numbers::pi / 180.f;
    static float fov = tanf(halfFovRads);

    static Vector3 cameraPos{0, 0, 0};

    static Raytracer raytracer;

    for(int h=0; h < height; ++h) 
    {
        for(int w=0; w < width; ++w) 
        {
            float ndc_x = ((float)w + 0.5f) / (float)width;  // [0, 1]
            float ndc_y = ((float)h + 0.5f) / (float)height; // [0, 1]

            float plane_x = (2.f * ndc_x) - 1.f; // [-1, 1]
            float plane_y = 1.f - 2.f * ndc_y;  // [-1, 1]
            
            plane_x *= fov;
            plane_y *= fov;

            plane_x *= aspect_ratio;

            Vector3 planePoint{plane_x, plane_y, -1.f};

            Vector3 rayDir = planePoint - cameraPos;
            rayDir = rayDir.Normalized();

            Ray ray{cameraPos, rayDir};

            XColor pixelColor = raytracer.RayTrace(ray, *this);

            SDL_SetRenderDrawColor(this->renderer, pixelColor.R * 255.f, pixelColor.G * 255.f, pixelColor.B * 255.f, 255);
            SDL_RenderDrawPoint(this->renderer, w, h);
        }   
    }
}