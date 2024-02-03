/**
 * @file Matrix4x4.h
 * @author Peter Garrod (p.glgarrod@gmail.com)
 * @brief 
 * @version 0.1
 * @date 03-02-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <cstddef>

#include "Vector4.h"

struct Matrix4x4
{
public:
    Matrix4x4();
    Matrix4x4(float s);
    Matrix4x4(const Matrix4x4& m);

    Vector4& operator[](size_t i);
    const Vector4& operator[](size_t i) const;

private:
    // Encapsulated array of vectors
    Vector4 m_Columns[4];
};

#endif