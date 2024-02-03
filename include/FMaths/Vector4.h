/**
 * @file Vector4.h
 * @author Peter Garrod (p.glgarrod@gmail.com)
 * @brief 
 * @version 0.1
 * @date 03-02-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef VECTOR4_H
#define VECTOR4_H

#include <cstddef>

struct Vector3;

struct Vector4
{
    // Constructors
    Vector4();
    Vector4(float x, float y, float z, float w = 1);
    Vector4(const Vector4& v);
    Vector4(const Vector3& v, float w = 1);

    // Member Variables
    float X, Y, Z, W;

    // Functions
    float Length() const;
    float LengthSquared() const;

    bool IsNormalized() const;

    Vector4& Normalize();
    Vector4 Normalized() const;

    float Dot(const Vector4& v) const;
    Vector4 Cross(const Vector4& v) const;

    // Operators
    // # Arithmetic
    // ## Vector
    Vector4 operator+(const Vector4& v) const;
    Vector4 operator-(const Vector4& v) const;

    Vector4& operator+=(const Vector4& v);
    Vector4& operator-=(const Vector4& v);

    // ## Scalar
    Vector4 operator*(float s) const;
    Vector4 operator/(float s) const;

    Vector4& operator*=(float s);
    Vector4& operator/=(float s);

    // # Accessor
    float& operator[](size_t i);
};

#endif