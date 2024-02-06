#include "FMaths/Quaternion.h"

#include <cmath>
#include <cassert>

#include "FMaths/Vector3.h"
#include "FMaths/Vector4.h"

Quaternion::Quaternion():
    x(0.f), y(0.f), z(0.f), w(1.f)
{}

Quaternion::Quaternion(float x, float y, float z, float w):
    x(x), y(y), z(z), w(w)
{}

Quaternion::Quaternion(const Vector3& axis, float r)
{
    // Angle is halved, as actual applied rotation = 2*r
    r *= 0.5f;

    float sinr, cosr;
    sincosf(r, &sinr, &cosr);

    Vector3 uv = axis.Normalized() * sinr;

    x = uv.x;
    y = uv.y;
    z = uv.z;
    w = cosr;
}

Quaternion::Quaternion(const Vector4 & v):
    x(v.x), y(v.y), z(v.z), w(v.w)
{}

Quaternion::Quaternion(const Quaternion & q):
    x(q.x), y(q.y), z(q.z), w(q.w)
{}

float Quaternion::Magnitude() const
{
    return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
}

float Quaternion::MagnitudeSquared() const
{
    return (x * x) + (y * y) + (z * z) + (w * w);
}

Quaternion& Quaternion::Normalize()
{
    if (IsNormalized())
        return *this;
    
    return (*this) *= (1.f / Magnitude());
}

Quaternion Quaternion::Normalized() const
{
    if (IsNormalized())
        return Quaternion(*this);
    
    return (*this) * (1.f / Magnitude());
}

bool Quaternion::IsNormalized() const
{
    return fabsf(MagnitudeSquared() - 1) <= __FLT_EPSILON__;
}

float Quaternion::Dot(const Quaternion& q) const
{
    return (x * q.x) + (y * q.y) + (z * q.z) + (w * q.w);
}

Vector3 Quaternion::Apply(const Vector3& v) const
{
    // Unit quaternions are easier to inverse
    if (!IsNormalized())
        return Normalized().Apply(v);

    Quaternion vQ(v.x, v.y, v.z, 0.f);
    // q * p * q^-1 negates scalar part
    // if q is unit quaterion then q = q^-1
    vQ = ((*this) * vQ) * (*this);

    return Vector3(vQ.x, vQ.y, vQ.z);
}

Vector4 Quaternion::Apply(const Vector4 & v) const
{
    // Strip and replace w component
    return Vector4(Apply(Vector3(v)), v.w);
}

Quaternion Quaternion::operator*(float s) const
{
    return Quaternion(x * s, y * s, z * s, w * s);
}

Quaternion Quaternion::operator/(float s) const
{
    return Quaternion(x / s, y / s, z / s, w / s);
}

Quaternion& Quaternion::operator*=(float s)
{
    x *= s;
    y *= s;
    z *= s;
    w *= s;

    return *this;
}

Quaternion& Quaternion::operator/=(float s)
{
    x /= s;
    y /= s;
    z /= s;
    w /= s;

    return *this;
}

Quaternion Quaternion::operator*(const Quaternion & q) const
{
    Vector3 vecA(x, y, z);
    Vector3 vecB(q.x, q.y, q.z);

    Vector3 outVec = (vecB * w) + (vecA * q.w) + vecA.Cross(vecB);
    float outW = (w * q.w) - vecA.Dot(vecB);
    
    return Quaternion(outVec.x, outVec.y, outVec.z, outW);
}

Quaternion & Quaternion::operator*=(const Quaternion & q)
{
    Vector3 vecA(x, y, z);
    Vector3 vecB(q.x, q.y, q.z);

    Vector3 resVec = (vecB * w) + (vecA * q.w) + vecA.Cross(vecB);

    x = resVec.x;
    y = resVec.y;
    z = resVec.z;
    w = (w * q.w) - vecA.Dot(vecB);

    return *this;
}

Quaternion Quaternion::operator+(const Quaternion &q) const
{
    return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
}

Quaternion Quaternion::operator-(const Quaternion &q) const
{
    return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w);
}

Quaternion& Quaternion::operator+=(const Quaternion& q)
{
    x += q.x;
    y += q.y;
    z += q.z;
    w += q.w;

    return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& q)
{
    x -= q.x;
    y -= q.y;
    z -= q.z;
    w -= q.w;

    return *this;
}

Quaternion& Quaternion::operator=(const Quaternion& q)
{
    x = q.x;
    y = q.y;
    z = q.z;
    w = q.w;

    return *this;
}

bool Quaternion::operator==(const Quaternion& q) const
{
    return (x == q.x) && (y == q.y) && (z == q.z) && (w == q.w);
}

bool Quaternion::operator!=(const Quaternion & q) const
{
    return (x != q.x) || (y != q.y) || (z != q.z) || (w != q.w);
}

float& Quaternion::operator[](size_t i)
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

const float& Quaternion::operator[](size_t i) const
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