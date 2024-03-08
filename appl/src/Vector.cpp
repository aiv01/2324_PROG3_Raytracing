#include "Vector3.h"
#include <cmath>

 Vector3::Vector3(float InX, float InY, float InZ) 
    : X(InX), Y(InY), Z(InZ) { }

Vector3 Vector3::operator-(const Vector3& InOther) const
{
    return Vector3{X - InOther.X, Y - InOther.Y, Z - InOther.Z};
}

Vector3 Vector3::operator/(const float InScalar) const
{
    return Vector3{X / InScalar, Y / InScalar, Z / InScalar};
}

Vector3 Vector3::Normalized() const 
{
    return *this / Magnetude();
}

float Vector3::Magnetude() const 
{
    //return sqrtf(X * X + Y * Y + Z * Z);
    return sqrtf(MagnetudeSquared());
}

float Vector3::MagnetudeSquared() const 
{
    return Dot(*this);
}

float Vector3::Dot(const Vector3& InOther) const
{
    return X * InOther.X + Y * InOther.Y + Z * InOther.Z;
}