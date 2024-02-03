#include "FMaths/Vector3.h"

#include <math.h>

Vector3::Vector3():
    X(0.f), Y(0.f), Z(0.f)
{}

Vector3::Vector3(const float & x, const float & y, const float & z):
    X(x), Y(y), Z(z)
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
    return fabsf(LengthSquared() - 1) < __FLT_EPSILON__;
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

Vector3 Vector3::operator*(const float& s) const
{
    return Vector3(X * s, Y * s, Z * s);
}

Vector3 Vector3::operator/(const float& s) const
{
    return Vector3(X / s, Y / s, Z / s);
}

Vector3 & Vector3::operator*=(const float & s)
{
    X *= s;
    Y *= s;
    Z *= s;

    return *this;
}

Vector3 & Vector3::operator/=(const float & s)
{
    X /= s;
    Y /= s;
    Z /= s;

    return *this;
}