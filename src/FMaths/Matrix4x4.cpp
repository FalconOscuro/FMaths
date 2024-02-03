#include "FMaths/Matrix4x4.h"

#include <cassert>

Matrix4x4::Matrix4x4()
{}

Matrix4x4::Matrix4x4(float s)
{
    for (size_t i = 0; i < 4; i++)
        m_Columns[i][i] = s;
}

Matrix4x4::Matrix4x4(const Matrix4x4& m)
{
    for (size_t i = 0; i < 4; i++)
        m_Columns[i] = m[i];
}

Vector4 & Matrix4x4::operator[](size_t i)
{
    assert(i < 4);
    return m_Columns[i];
}

const Vector4& Matrix4x4::operator[](size_t i) const
{
    assert(i < 4);
    return m_Columns[i];
}