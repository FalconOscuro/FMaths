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

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 & m) const
{
    Matrix4x4 res = Matrix4x4();

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            for (size_t k = 0; k < 4; k++)
                res[i][j] += m_Columns[k][j] * m[i][k];
    
    return res;
}

Matrix4x4 & Matrix4x4::operator*=(const Matrix4x4& m)
{
    // Cannot multiply in place, leads to incorrect behaviour
    return operator=(operator*(m));
}

Vector4 Matrix4x4::operator*(const Vector4 & v) const
{
    Vector4 res = Vector4();

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            res[i] += v[i] * operator[](j)[i];
    
    return res;
}

Matrix4x4 & Matrix4x4::operator=(const Matrix4x4 & m)
{
    for (size_t i = 0; i < 4; i++)
        m_Columns[i] = m[i];
    
    return *this;
}

bool Matrix4x4::operator==(const Matrix4x4& m) const
{
    bool equal = true;

    for (size_t i = 0; i < 4; i++)
        equal &= operator[](i) == m[i];
    
    return equal;
}

bool Matrix4x4::operator!=(const Matrix4x4 & m) const
{
    bool nEqual = false;

    for (size_t i = 0; i < 4; i++)
        nEqual |= operator[](i) != m[i];
    
    return nEqual;
}

Matrix4x4 Matrix4x4::Identity()
{
    return Matrix4x4(1);
}

Matrix4x4 Matrix4x4::Translate(const Vector3& v)
{
    Matrix4x4 trans = Matrix4x4(1);
    trans[3] = v;

    return trans;
}

Matrix4x4 Matrix4x4::Scale(const Vector3& v)
{
    Matrix4x4 scale = Matrix4x4(1);

    for (size_t i = 0; i < 3; i++)
        scale[i][i] = v[i];
    
    return scale;
}

Matrix4x4 Matrix4x4::QuatRotate(const Vector4 & q)
{
    Matrix4x4 rot = Matrix4x4();

    rot[0] = Vector4(
        (2 * ((q.x * q.x) + (q.w * q.w))) - 1,
         2 * ((q.x * q.y) + (q.w * q.z)),
         2 * ((q.x * q.z) - (q.w * q.y)),
         0
    );

    rot[1] = Vector4(
         2 * ((q.y * q.x) - (q.w * q.z)),
        (2 * ((q.y * q.y) + (q.w * q.w))) - 1,
         2 * ((q.y * q.z) + (q.w * q.x)),
         0
    );

    rot[2] = Vector4(
         2 * ((q.z * q.x) + (q.w * q.y)),
         2 * ((q.z * q.y) - (q.w * q.x)),
        (2 * ((q.z * q.z) + (q.w * q.w))) - 1,
        0
    );

    rot[3][3] = 1;
    return rot;
}