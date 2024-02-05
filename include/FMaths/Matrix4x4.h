/**
 * @file Matrix4x4.h
 * @author Peter Garrod (p.glgarrod@gmail.com)
 * @brief 4x4 Matrix, useful for transformations
 * @version 0.1
 * @date 03-02-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <cstddef>

#include "Vector3.h"
#include "Vector4.h"

/**
 * @brief 4x4 Matrix of floats, useful for transformations
 * 
 */
struct Matrix4x4
{
public:
    /**
     * @brief Default constructor
     */
    Matrix4x4();

    /**
     * @brief Construct a Matrix with all of the central diagonal elements set to s
     * 
     * @param s Diagonal value
     */
    Matrix4x4(float s);

    /**
     * @brief Copy Constructor
     */
    Matrix4x4(const Matrix4x4& m);

    /**
     * @brief Accessor for matrix data in column major ordering
     */
    Vector4& operator[](size_t i);

    /**
     * @brief Constant accessor
     */
    const Vector4& operator[](size_t i) const;

    /**
     * @brief Matrix multiplication
     */
    Matrix4x4 operator*(const Matrix4x4& m) const;

    /**
     * @brief Matrix multiplication assignment
     */
    Matrix4x4& operator*=(const Matrix4x4& m);

    /**
     * @brief Matrix vector multiplication
     */
    Vector4 operator*(const Vector4& v) const;

    /**
     * @brief Assignment operator
     */
    Matrix4x4& operator=(const Matrix4x4& m);

    /**
     * @brief Equatable
     * @note Does not account for floating point precision errors
     */
    bool operator==(const Matrix4x4& m) const;

    /**
     * @brief Inequatable
     * @note Does not account for floating point precision errors
     */
    bool operator!=(const Matrix4x4& m) const;

    /**
     * @brief Creates an Identity matrix
     */
    static Matrix4x4 Identity();

    /**
     * @brief Creates a translation matrix
     * 
     * @param v Translation
     */
    static Matrix4x4 Translate(const Vector3& v);

    /**
     * @brief Creates a scaling matrix
     * 
     * @param v Scaling
     */
    static Matrix4x4 Scale(const Vector3& v);

    /**
     * @brief Creates a rotation matrix from a quaternion
     * 
     * @param q Quaternion rotation
     * @todo Quaternion implemention
     */
    static Matrix4x4 QuatRotate(const Vector4& q);

private:
    
    /**
     * @brief Encapsulated matrix
     * 
     * Organized as an array of vector4 in column major ordering.
     */
    Vector4 m_Columns[4];
};

#endif