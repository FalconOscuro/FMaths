/**
 * @file Vector3.h
 * @author Peter Garrod (p.glgarrod@gmail.com)
 * @brief 
 * @version 0.1
 * @date 03-02-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef VECTOR3_H
#define VECTOR3_H

#include <cstddef>

struct Vector2;
struct Vector4;

/**
 * @brief 3D Vector of floats X, Y, Z
 */
struct Vector3
{
    // Constructors
    /**
     * @brief Construct a new Vector3 object (0, 0, 0)
     */
    Vector3();

    /**
     * @brief Construct a new Vector3 object given X, Y Z
     */
    Vector3(float x, float y, float z);

    Vector3(const Vector2& v, float z = 0);
    Vector3(const Vector3& v);
    Vector3(const Vector4& v);

    // Varaiables
    float x, y, z;

    // Functions

    /**
     * @brief Get vector length
     */
    float Length() const;

    /**
     * @brief Get vector length squared
     * @note Useful for checking if normalized, as sqrt 1 == 1, avoiding sqrt operator
     */
    float LengthSquared() const;

    /**
     * @brief Turn vector to normalized unit vector
     */
    Vector3& Normalize();

    /**
     * @brief Get normalized version of this vector
     */
    Vector3 Normalized() const;

    /**
     * @brief Is this a normalized unit vector
     */
    bool IsNormalized() const;

    /**
     * @brief Vector dot product
     */
    float Dot(const Vector3& v) const;

    /**
     * @brief Vector cross product
     */
    Vector3 Cross(const Vector3& v) const;

    // Operators
    // # Arithmetic
    // ## Vector
    Vector3 operator+(const Vector3& v) const;
    Vector3 operator-(const Vector3& v) const;

    Vector3& operator+=(const Vector3& v);
    Vector3& operator-=(const Vector3& v);

    // ## Scalar
    Vector3 operator*(float s) const;
    Vector3 operator/(float s) const;

    Vector3& operator*=(float s);
    Vector3& operator/=(float s);

    // ## Binary
    bool operator==(const Vector3& v) const;
    bool operator!=(const Vector3& v) const;

    // # Accessor
    float& operator[](size_t i);
};

#endif