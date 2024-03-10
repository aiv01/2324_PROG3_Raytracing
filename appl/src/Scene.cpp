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

Scene::Scene(int InWidth, int InHeight, SDL_Renderer* InRender) 
{
   Width = InWidth;
   Height = InHeight;
   Renderer = InRender;

   Sphere Sphere01{Vector3{0, 0, -5}, 2.f};
   Spheres.push_back(Sphere01);
}

Scene::~Scene() 
{

}

void Scene::Update(float delta_time) 
{   
    static float AspectRatio = (float)Width / (float)Height;

    static float VerticalFovDegrees = 60.f;
    static float HalfFovRadiants = (VerticalFovDegrees * 0.5f) * std::numbers::pi / 180.f;
    static float Fov = tanf(HalfFovRadiants);

    static Vector3 CameraPosition{0, 0, 0};
    static Raytracer Raytracer;

    for(int H = 0; H < Height; ++H) 
    {
        for(int W = 0; W < Width; ++W) 
        {
            float NDC_X = ((float)W + 0.5f) / (float)Width;  // [0, 1]
            float NDC_Y = ((float)H + 0.5f) / (float)Height; // [0, 1]

            float Plane_X = (2.f * NDC_X) - 1.f; // [-1, 1]
            float Plane_Y = 1.f - 2.f * NDC_Y;  // [-1, 1]
            
            Plane_X *= Fov * AspectRatio;
            Plane_Y *= Fov;

            Vector3 planePoint{Plane_X, Plane_Y, -1.f};

            Vector3 rayDir = planePoint - CameraPosition;
            rayDir = rayDir.Normalized();

            Ray ray{CameraPosition, rayDir};

            XColor pixelColor = Raytracer.RayTrace(ray, *this);

            SDL_SetRenderDrawColor(this->Renderer, pixelColor.R * 255.f, pixelColor.G * 255.f, pixelColor.B * 255.f, 255);
            SDL_RenderDrawPoint(this->Renderer, W, H);
        }   
    }
}