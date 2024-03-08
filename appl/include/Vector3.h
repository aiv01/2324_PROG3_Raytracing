#pragma once

struct Vector3 {
    float X;
    float Y;
    float Z;

    Vector3(float InX, float InY, float InZ);

    Vector3 operator-(const Vector3& InOther) const;

    Vector3 operator/(const float InScalar) const;

    Vector3 Normalized() const;

    float Magnetude() const;
};