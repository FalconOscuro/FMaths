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

struct Vector2;
struct Vector3;

/**
 * @brief 4D vector
 * 
 * @note Designed to be used with Matrix4x4
 */
struct Vector4
{
    /**
     * @brief Default constructor
     */
    Vector4();

    /**
     * @brief Basic constructor from x, y, z, w members
     */
    Vector4(float x, float y, float z, float w = 1);

    /**
     * @brief Construct from 2D vector
     */
    Vector4(const Vector2& v, float z = 0, float w = 1);

    /**
     * @brief Construct from 3D vector
     */
    Vector4(const Vector3& v, float w = 1);

    /**
     * @brief Copy constructor
     */
    Vector4(const Vector4& v);

    /**
     * @brief Vector axes
     */
    float x, y, z, w;

    /**
     * @brief Magnitude/Length of vector
     */
    float Length() const;

    /**
     * @brief Magnitude/Length squared of vector
     * 
     * @note Avoid sqrt operations, useful for checking if normalized
     */
    float LengthSquared() const;

    /**
     * @brief True if this is a normalized unit vector
     */
    bool IsNormalized() const;

    /**
     * @brief Convert to normalized unit vector
     */
    Vector4& Normalize();

    /**
     * @brief Get Normalized copy
     */
    Vector4 Normalized() const;

    /**
     * @brief Vector dot product
     */
    float Dot(const Vector4& v) const;

    /**
     * @brief Vector cross product
     */
    Vector4 Cross(const Vector4& v) const;

    /**
     * @brief Vector addition
     */
    Vector4 operator+(const Vector4& v) const;

    /**
     * @brief Vector subtraction
     */
    Vector4 operator-(const Vector4& v) const;

    /**
     * @brief Vector addition assignment
     */
    Vector4& operator+=(const Vector4& v);

    /**
     * @brief Vector subtraction assignment
     */
    Vector4& operator-=(const Vector4& v);

    /**
     * @brief Scalar multiplication
     */
    Vector4 operator*(float s) const;

    /**
     * @brief Scalar division
     */
    Vector4 operator/(float s) const;

    /**
     * @brief Scalar multiplication assignment
     */
    Vector4& operator*=(float s);

    /**
     * @brief Scalar division assignment
     */
    Vector4& operator/=(float s);

    /**
     * @brief Equatable operator
     */
    bool operator==(const Vector4& v) const;

    /**
     * @brief Inequatable operator
     */
    bool operator!=(const Vector4& v) const;

    /**
     * @brief Assignment operator
     */
    Vector4& operator=(const Vector4& v);

    /**
     * @brief Access vector as an array
     */
    float& operator[](size_t i);

    /**
     * @brief Constant accessor as array
     */
    const float& operator[](size_t i) const;
};

#endif