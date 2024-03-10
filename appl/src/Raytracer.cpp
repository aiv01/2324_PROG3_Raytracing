#include "Raytracer.h"
#include "Sphere.h"

XColor Raytracer::RayTrace(const Ray& InRay, Scene& InScene)
{
    //TODO: handle multiple sphere
    Sphere& Sphere = InScene.Spheres[0];

    Vector3 L = Sphere.Center - InRay.Origin;
    float Tca = L.Dot(InRay.Direction);

    float MagnL2 = L.MagnetudeSquared();

    float D2 = MagnL2 - Tca * Tca;
    float Radius2 = Sphere.Radius * Sphere.Radius;
    if (D2 > Radius2) return {0, 0, 0};

    float Thc = sqrtf(Radius2 - D2);

    float T0 = Tca - Thc; //
    float T1 = Tca + Thc;

    if (T1 < T0)  //In T0 we will keep the smallest value
    {
        float Temp = T0;
        T0 = T1;
        T1 = Temp;
    }

    if (T0 < 0) 
    {
        T0 = T1; //Case: where T1 > T0
        if (T0 < 0) return {0, 0, 0};
    }

    return {1, 0, 0};
}