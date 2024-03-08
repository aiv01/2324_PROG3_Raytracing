#include "Raytracer.h"
#include "Sphere.h"

XColor Raytracer::RayTrace(const Ray& InRay, Scene& InScene)
{
    //static Sphere sphere{Vector3{0, 0, -5}, 2.f};
    Sphere& sphere = InScene.spheres[0];

    Vector3 L = sphere.Center - InRay.Origin;
    float Tca = L.Dot(InRay.Direction);

    float magnL2 = L.MagnetudeSquared();

    float d2 = magnL2 - Tca * Tca;
    float radius2 = sphere.Radius * sphere.Radius;
    if (d2 > radius2) return {0, 0, 0};

    float Thc = sqrtf(radius2 - d2);

    float T0 = Tca - Thc; //
    float T1 = Tca + Thc;

    if (T1 < T0)  //In T0 we will keep the smallest value
    {
        float temp = T0;
        T0 = T1;
        T1 = temp;
    }

    if (T0 < 0) 
    {
        T0 = T1; //Case: where T1 > T0
        if (T0 < 0) return {0, 0, 0};
    }

    return {1, 0, 0};
}