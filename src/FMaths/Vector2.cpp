#include "FMaths/Vector2.h"

#include <cmath>
#include <cassert>

#include "FMaths/Vector3.h"
#include "FMaths/Vector4.h"

Vector2::Vector2():
    x(0), y(0)
{}

Vector2::Vector2(float x, float y):
    x(x), y(y)
{}

Vector2::Vector2(const Vector2 & v):
    x(v.x), y(v.y)
{}

Vector2::Vector2(const Vector3 & v):
    x(v.x), y(v.y)
{}

Vector2::Vector2(const Vector4 & v):
    x(v.x), y(v.y)
{}

float Vector2::Length() const
{
    return sqrtf((x * x) + (y * y));
}

float Vector2::LengthSquared() const
{
    return (x * x) + (y * y);
}

Vector2& Vector2::Normalize()
{
    if (IsNormalized())
        return *this;
    
    return operator/=(Length());
}

Vector2 Vector2::Normalized() const
{
    if (IsNormalized())
        return Vector2(*this);
    
    return operator/(Length());
}

bool Vector2::IsNormalized() const
{
    return fabsf(LengthSquared() - 1) <= __FLT_EPSILON__;
}

float Vector2::Dot(const Vector2& v) const
{
    return (x * v.x) + (y * v.y);
}

Vector2 Vector2::operator+(const Vector2& v) const
{
    return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v) const
{
    return Vector2(x - v.x, y - v.y);
}

Vector2& Vector2::operator+=(const Vector2& v)
{
    x += v.x;
    y += v.y;

    return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
    x -= v.x;
    y -= v.y;

    return *this;
}

Vector2 Vector2::operator*(float s) const
{
    return Vector2(x * s, y * s);
}

Vector2 Vector2::operator/(float s) const
{
    return Vector2(x / s, y / s);
}

Vector2& Vector2::operator*=(float s)
{
    x *= s;
    y *= s;

    return *this;
}

Vector2& Vector2::operator/=(float s)
{
    x /= s;
    y /= s;

    return *this;
}

bool Vector2::operator==(const Vector2& v) const
{
    return (x == v.x) && (y == v.y);
}

bool Vector2::operator!=(const Vector2& v) const
{
    return (x != v.x) || (y != v.y);
}

Vector2& Vector2::operator=(const Vector2& v)
{
    assert(this != &v);

    x = v.x;
    y = v.y;
    return *this;
}

float & Vector2::operator[](size_t i)
{
    assert(i < 2);

    switch (i)
    {
    default:
    case 0:
        return x;

    case 1:
        return y;
    }
}

const float& Vector2::operator[](size_t i) const
{
    assert(i < 2);

    switch (i)
    {
    default:
    case 0:
        return x;
    
    case 1:
        return y;
    }
}