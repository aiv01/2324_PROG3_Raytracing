#pragma once
#include "Vector3.h"

struct Sphere 
{
    Vector3 Center;
    float Radius;

    Sphere(const Vector3& InCenter, float InRadius);
};