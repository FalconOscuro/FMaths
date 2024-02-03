#include "FMaths/Vector3.h"

#include <math.h>
#include <cassert>

#include "FMaths/Vector2.h"
#include "FMaths/Vector4.h"

Vector3::Vector3():
    x(0), y(0), z(0)
{}

Vector3::Vector3(float x, float y, float z):
    x(x), y(y), z(z)
{}

Vector3::Vector3(const Vector2 & v, float z):
    x(v.x), y(v.y), z(z)
{}

Vector3::Vector3(const Vector3& v):
    x(v.x), y(v.y), z(v.z)
{}

Vector3::Vector3(const Vector4& v):
    x(v.x), y(v.y), z(v.z)
{}

float Vector3::Length() const
{
    return sqrtf(x*x + y*y + z*z);
}

float Vector3::LengthSquared() const
{
    return x*x + y*y + z*z;
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
    return (x * v.x) + (y * v.y) + (z * v.z);
}

Vector3 Vector3::Cross(const Vector3 & v) const
{
    return Vector3(
        (y * v.z) - (z * v.y),
        (z * v.x) - (x * v.z),
        (x * v.y) - (y * v.x)
    );
}

Vector3 Vector3::operator+(const Vector3& v) const
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3& v) const
{
    return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3& Vector3::operator+=(const Vector3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

Vector3 Vector3::operator*(float s) const
{
    return Vector3(x * s, y * s, z * s);
}

Vector3 Vector3::operator/(float s) const
{
    return Vector3(x / s, y / s, z / s);
}

Vector3 & Vector3::operator*=(float s)
{
    x *= s;
    y *= s;
    z *= s;

    return *this;
}

Vector3 & Vector3::operator/=(float s)
{
    x /= s;
    y /= s;
    z /= s;

    return *this;
}

bool Vector3::operator==(const Vector3& v) const
{
    // account for precision?
    return (x == v.x) && (y == v.y) && (z == v.z);
}

bool Vector3::operator!=(const Vector3 & v) const
{
    return (x != v.x) || (y != v.y) || (z != v.z);
}

float& Vector3::operator[](size_t i)
{
    assert(i < 3);

    switch (i)
    {
    default:
    case 0:
        return x;
    
    case 1:
        return y;
    
    case 2:
        return z;
    }
}