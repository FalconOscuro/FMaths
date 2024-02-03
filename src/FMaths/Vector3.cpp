#include "FMaths/Vector3.h"

#include <math.h>
#include <cassert>

#include "FMaths/Vector4.h"

Vector3::Vector3():
    X(0), Y(0), Z(0)
{}

Vector3::Vector3(float x, float y, float z):
    X(x), Y(y), Z(z)
{}

Vector3::Vector3(const Vector3& v):
    X(v.X), Y(v.Y), Z(v.Z)
{}

Vector3::Vector3(const Vector4& v):
    X(v.X), Y(v.Y), Z(v.Z)
{}

float Vector3::Length() const
{
    return sqrtf(X*X + Y*Y + Z*Z);
}

float Vector3::LengthSquared() const
{
    return X*X + Y*Y + Z*Z;
}

Vector3& Vector3::Normalize()
{
    // Speed improvement from caching LengthSquared()?
    // Already normalized, avoids sqrt operator
    if (IsNormalized())
        return *this;

    return operator/=(Length());
}

Vector3 Vector3::Normalized() const
{
    // Already normalized, avoids sqrt operator
    if (IsNormalized())
        return Vector3(*this);
    
    // Square already calculated
    return operator/(Length());
}

bool Vector3::IsNormalized() const
{
    // Accounting for floating point innaccuracy
    // FLT_EPSILON is most accurate near 1.0
    return fabsf(LengthSquared() - 1) <= __FLT_EPSILON__;
}

float Vector3::Dot(const Vector3& v) const
{
    return (X * v.X) + (Y * v.Y) + (Z * v.Z);
}

Vector3 Vector3::Cross(const Vector3 & v) const
{
    return Vector3(
        (Y * v.Z) - (Z * v.Y),
        (Z * v.X) - (X * v.Z),
        (X * v.Y) - (Y * v.X)
    );
}

Vector3 Vector3::operator+(const Vector3& v) const
{
    return Vector3(X + v.X, Y + v.Y, Z + v.Z);
}

Vector3 Vector3::operator-(const Vector3& v) const
{
    return Vector3(X - v.X, Y - v.Y, Z - v.Z);
}

Vector3& Vector3::operator+=(const Vector3& v)
{
    X += v.X;
    Y += v.Y;
    Z += v.Z;

    return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
    X -= v.X;
    Y -= v.Y;
    Z -= v.Z;

    return *this;
}

Vector3 Vector3::operator*(float s) const
{
    return Vector3(X * s, Y * s, Z * s);
}

Vector3 Vector3::operator/(float s) const
{
    return Vector3(X / s, Y / s, Z / s);
}

Vector3 & Vector3::operator*=(float s)
{
    X *= s;
    Y *= s;
    Z *= s;

    return *this;
}

Vector3 & Vector3::operator/=(float s)
{
    X /= s;
    Y /= s;
    Z /= s;

    return *this;
}

float& Vector3::operator[](size_t i)
{
    assert(i < 3);

    switch (i)
    {
    default:
    case 0:
        return X;
    
    case 1:
        return Y;
    
    case 2:
        return Z;
    }
}