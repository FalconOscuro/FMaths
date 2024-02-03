#include "FMaths/Vector4.h"

#include <cmath>
#include <cassert>

#include "FMaths/Vector3.h"

Vector4::Vector4():
    X(0), Y(0), Z(0), W(1)
{}

Vector4::Vector4(float x, float y, float z, float w):
    X(x), Y(y), Z(z), W(w)
{}

Vector4::Vector4(const Vector4& v):
    X(v.X), Y(v.Y), Z(v.Z), W(v.W)
{}

Vector4::Vector4(const Vector3 & v, float w):
    X(v.X), Y(v.Y), Z(v.Z), W(w)
{}

float Vector4::Length() const
{
    return sqrtf((X * X) + (Y * Y) + (Z * Z) + (W * W));
}

float Vector4::LengthSquared() const
{
    return (X * X) + (Y * Y) + (Z * Z) + (W * W);
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
    return (X * v.X) + (Y * v.Y) + (Z * v.Z) + (W * v.W);
}

Vector4 Vector4::Cross(const Vector4 & v) const
{
    return Vector4(
        (Y * v.Z) - (Z * v.Y),
        (Z * v.X) - (X * v.Z),
        (X * v.Y) - (Y * v.X)
    );
}

Vector4 Vector4::operator+(const Vector4& v) const
{
    return Vector4(X + v.X, Y + v.Y, Z + v.Z, W + v.W);
}

Vector4 Vector4::operator-(const Vector4& v) const
{
    return Vector4(X - v.X, Y - v.Y, Z - v.Z, W - v.W);
}

Vector4& Vector4::operator+=(const Vector4& v)
{
    X += v.X;
    Y += v.Y;
    Z += v.Z;
    W += v.W;

    return *this;
}

Vector4& Vector4::operator-=(const Vector4& v)
{
    X -= v.X;
    Y -= v.Y;
    Z -= v.Z;
    W -= v.W;

    return *this;
}

Vector4 Vector4::operator*(float s) const
{
    return Vector4(X * s, Y * s, Z * s, W * s);
}

Vector4 Vector4::operator/(float s) const
{
    return Vector4(X / s, Y / s, Z / s, W / s);
}

Vector4& Vector4::operator*=(float s)
{
    X *= s;
    Y *= s;
    Z *= s;
    W *= s;

    return *this;
}

Vector4 & Vector4::operator/=(float s)
{
    X /= s;
    Y /= s;
    Z /= s;
    W /= s;

    return *this;
}

float & Vector4::operator[](size_t i)
{
    assert(i < 4);

    switch (i)
    {
    default:
    case 0:
        return X;
    
    case 1:
        return Y;

    case 2:
        return Z;

    case 3:
        return W;
    }
}