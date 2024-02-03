#include "FMaths/Vector4.h"

#include <cmath>
#include <cassert>

#include "FMaths/Vector2.h"
#include "FMaths/Vector3.h"

Vector4::Vector4():
    x(0), y(0), z(0), w(1)
{}

Vector4::Vector4(float x, float y, float z, float w):
    x(x), y(y), z(z), w(w)
{}

Vector4::Vector4(const Vector2 & v, float z, float w):
    x(v.x), y(v.y), z(z), w(w)
{}

Vector4::Vector4(const Vector3 & v, float w):
    x(v.x), y(v.y), z(v.z), w(w)
{}

Vector4::Vector4(const Vector4& v):
    x(v.x), y(v.y), z(v.z), w(v.w)
{}

float Vector4::Length() const
{
    return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
}

float Vector4::LengthSquared() const
{
    return (x * x) + (y * y) + (z * z) + (w * w);
}

bool Vector4::IsNormalized() const
{
    return fabsf(LengthSquared() - 1) <= __FLT_EPSILON__;
}

Vector4& Vector4::Normalize()
{
    if (IsNormalized())
        return *this;
    
    return operator/=(Length());
}

Vector4 Vector4::Normalized() const
{
    if (IsNormalized())
        return Vector4(*this);

    return operator/(Length());
}

float Vector4::Dot(const Vector4& v) const
{
    return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w);
}

Vector4 Vector4::Cross(const Vector4 & v) const
{
    return Vector4(
        (y * v.z) - (z * v.y),
        (z * v.x) - (x * v.z),
        (x * v.y) - (y * v.x)
    );
}

Vector4 Vector4::operator+(const Vector4& v) const
{
    return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vector4 Vector4::operator-(const Vector4& v) const
{
    return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
}

Vector4& Vector4::operator+=(const Vector4& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;

    return *this;
}

Vector4& Vector4::operator-=(const Vector4& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;

    return *this;
}

Vector4 Vector4::operator*(float s) const
{
    return Vector4(x * s, y * s, z * s, w * s);
}

Vector4 Vector4::operator/(float s) const
{
    return Vector4(x / s, y / s, z / s, w / s);
}

Vector4& Vector4::operator*=(float s)
{
    x *= s;
    y *= s;
    z *= s;
    w *= s;

    return *this;
}

Vector4 & Vector4::operator/=(float s)
{
    x /= s;
    y /= s;
    z /= s;
    w /= s;

    return *this;
}

bool Vector4::operator==(const Vector4& v) const
{
    return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
}

bool Vector4::operator!=(const Vector4& v) const
{
    return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w);
}

float & Vector4::operator[](size_t i)
{
    assert(i < 4);

    switch (i)
    {
    default:
    case 0:
        return x;
    
    case 1:
        return y;

    case 2:
        return z;

    case 3:
        return w;
    }
}