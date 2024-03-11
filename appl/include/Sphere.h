#pragma once
#include "Vector3.h"
#include "Color.h"

struct Material 
{
    XColor Albedo;
    float SpecularShiningFactor;
};

struct Sphere 
{
    Vector3 Center;
    float Radius;
    Material Material;

    Sphere(const Vector3& InCenter, float InRadius);
};