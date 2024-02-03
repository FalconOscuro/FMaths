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

/**
 * @brief 3D Vector of floats X, Y, Z
 */
class Vector3
{
public:

    // Constructors
    /**
     * @brief Construct a new Vector3 object (0, 0, 0)
     */
    Vector3();

    /**
     * @brief Construct a new Vector3 object given X, Y Z
     */
    Vector3(const float& x, const float& y, const float& z);

    // Varaiables
    float X, Y, Z;

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

    // Operators
    Vector3 operator+(const Vector3& v) const;
    Vector3 operator-(const Vector3& v) const;

    Vector3& operator+=(const Vector3& v);
    Vector3& operator-=(const Vector3& v);

    Vector3 operator*(const float& s) const;
    Vector3 operator/(const float& s) const;

    Vector3& operator*=(const float& s);
    Vector3& operator/=(const float& s);
};

#endif