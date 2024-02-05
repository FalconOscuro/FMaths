#include "FMaths/Matrix4x4.h"

#include <cassert>

Matrix4x4::Matrix4x4()
{}

Matrix4x4::Matrix4x4(float s)
{
    // Could be un-rolled
    for (size_t i = 0; i < 4; i++) // iterate diagonal
        m_Columns[i][i] = s;
}

Matrix4x4::Matrix4x4(const Matrix4x4& m)
{
    // Could be un-rolled
    for (size_t col = 0; col < 4; col++) // iterate columns
        m_Columns[col] = m[col];
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

    for (size_t col = 0; col < 4; col++) // column
        for (size_t row = 0; row < 4; row++) // row
            for (size_t i = 0; i < 4; i++) // multiply along current row/column
                res[col][row] += m_Columns[i][row] * m[col][i];
    
    return res;
}

Matrix4x4 & Matrix4x4::operator*=(const Matrix4x4& m)
{
    // Cannot multiply in place, leads to incorrect behaviour,
    // instead basic multiply and assignment operators are used in tandem
    return operator=(operator*(m));
}

Vector4 Matrix4x4::operator*(const Vector4 & v) const
{
    Vector4 res = Vector4();

    for (size_t row = 0; row < 4; row++) // row
        for (size_t col = 0; col < 4; col++) // column
            res[row] += v[row] * operator[](col)[row];
    
    return res;
}

Matrix4x4 & Matrix4x4::operator=(const Matrix4x4 & m)
{
    // Could be un-rolled, or memcpy used
    for (size_t col = 0; col < 4; col++)
        m_Columns[col] = m[col];
    
    return *this;
}

bool Matrix4x4::operator==(const Matrix4x4& m) const
{
    bool equal = true;

    // Could be un-rolled
    for (size_t col = 0; col < 4; col++)
        equal &= operator[](col) == m[col];
    
    return equal;
}

bool Matrix4x4::operator!=(const Matrix4x4 & m) const
{
    bool nEqual = false;

    // Could be un-rolled
    for (size_t col = 0; col < 4; col++)
        nEqual |= operator[](col) != m[col];
    
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
    Matrix4x4 scale = Matrix4x4();

    for (size_t i = 0; i < 3; i++) // iterate diagonal
        scale[i][i] = v[i];
    
    // Avoid double assignment along diagonal
    scale[3][3] = 1;

    return scale;
}

Matrix4x4 Matrix4x4::QuatRotate(const Vector4 & q)
{
    Matrix4x4 rot = Matrix4x4();

    // equation used: https://automaticaddison.com/wp-content/uploads/2020/09/quaternion-to-rotation-matrix.jpg
    // source: https://automaticaddison.com/how-to-convert-a-quaternion-to-a-rotation-matrix/
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