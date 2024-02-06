/**
 * @file Quaternion.h
 * @author Peter Garrod (p.glgarrod@gmail.com)
 * @brief 
 * @version 0.1
 * @date 06-02-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef QUATERNION_H
#define QUATERNION_H

#include <cstddef>

struct Vector3;
struct Vector4;

struct Quaternion
{
    /**
     * @brief Default constructor
     */
    Quaternion();

    /**
     * @brief Construct from components
     */
    Quaternion(float x, float y, float z, float w);

    /**
     * @brief Construct from an axis and rotation
     * 
     * @param axis Axis of rotation, will be converted to unit vector if not already
     * @param r Rotation about axis in radians
     */
    Quaternion(const Vector3& axis, float r);

    /**
     * @brief Vector 4 copy constructor
     * 
     * @note WARNING: This is a straight copy, no processing occurs
     */
    Quaternion(const Vector4& v);

    /**
     * @brief Copy constructor
     */
    Quaternion(const Quaternion& q);

    float x, y, z, w;

    float Magnitude() const;
    float MagnitudeSquared() const;

    Quaternion& Normalize();
    Quaternion Normalized() const;
    bool IsNormalized() const;

    float Dot(const Quaternion& q) const;

    Vector3 Apply(const Vector3& v) const;
    Vector4 Apply(const Vector4& v) const;

    Quaternion operator*(float s) const;
    Quaternion operator/(float s) const;
    
    Quaternion& operator*=(float s);
    Quaternion& operator/=(float s);

    Quaternion operator*(const Quaternion& q) const;
    Quaternion& operator*=(const Quaternion& q);
    // Divide?

    Quaternion operator+(const Quaternion& q) const;
    Quaternion operator-(const Quaternion& q) const;

    Quaternion& operator+=(const Quaternion& q);
    Quaternion& operator-=(const Quaternion& q);

    Quaternion& operator=(const Quaternion& q);

    bool operator==(const Quaternion& q) const;
    bool operator!=(const Quaternion& q) const;

    float& operator[](size_t i);
    const float& operator[](size_t i) const;
};

#endif