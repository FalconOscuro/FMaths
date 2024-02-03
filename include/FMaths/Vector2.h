/**
 * @file Vector2.h
 * @author Peter Garrod (p.glgarrod@gmail.com)
 * @brief 
 * @version 0.1
 * @date 03-02-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef VECTOR2_H
#define VECTOR2_H

#include <cstddef>

struct Vector3;
struct Vector4;

struct Vector2
{
    Vector2();
    Vector2(float x, float y);
    Vector2(const Vector2& v);
    Vector2(const Vector3& v);
    Vector2(const Vector4& v);

    float x, y;

    float Length() const;
    float LengthSquared() const;

    Vector2& Normalize();
    Vector2 Normalized() const;
    bool IsNormalized() const;

    float Dot(const Vector2& v) const;

    Vector2 operator+(const Vector2& v) const;
    Vector2 operator-(const Vector2& v) const;
    
    Vector2& operator+=(const Vector2& v);
    Vector2& operator-=(const Vector2& v);

    Vector2 operator*(float s) const;
    Vector2 operator/(float s) const;

    Vector2& operator*=(float s);
    Vector2& operator/=(float s);

    bool operator==(const Vector2& v) const;
    bool operator!=(const Vector2& v) const;

    Vector2& operator=(const Vector2& v);

    float& operator[](size_t i);
    const float& operator[](size_t i) const;
};


#endif