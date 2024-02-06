#include "FMaths/Matrix4x4.h"

#include <cmath>
#include <cassert>

Matrix4x4::Matrix4x4()
{}

Matrix4x4::Matrix4x4(float s)
{
    // Could be un-rolled
    for (size_t i = 0; i < 4; i++) // iterate diagonal
        m_Columns[i][i] = s;
}

Matrix4x4::Matrix4x4(const Vector4& col0, const Vector4& col1, const Vector4& col2, const Vector4& col3):
    m_Columns{col0, col1, col2, col3}
{}

Matrix4x4::Matrix4x4(const Matrix4x4& m)
{
    // Could be un-rolled
    for (size_t col = 0; col < 4; col++) // iterate columns
        m_Columns[col] = m[col];
}

Matrix4x4 Matrix4x4::Inverse() const
{
    // Find determinants for submatrices
    float s0 = (m_Columns[0][0] * m_Columns[1][1]) - (m_Columns[0][1] * m_Columns[1][0]);
    float s1 = (m_Columns[0][0] * m_Columns[1][2]) - (m_Columns[0][2] * m_Columns[1][0]);
    float s2 = (m_Columns[0][0] * m_Columns[1][3]) - (m_Columns[0][3] * m_Columns[1][0]);
    float s3 = (m_Columns[0][1] * m_Columns[1][2]) - (m_Columns[0][2] * m_Columns[1][1]);
    float s4 = (m_Columns[0][1] * m_Columns[1][3]) - (m_Columns[0][3] * m_Columns[1][1]);
    float s5 = (m_Columns[0][2] * m_Columns[1][3]) - (m_Columns[0][3] * m_Columns[1][2]);

    float c0 = (m_Columns[2][0] * m_Columns[3][1]) - (m_Columns[2][1] * m_Columns[3][0]);
    float c1 = (m_Columns[2][0] * m_Columns[3][2]) - (m_Columns[2][2] * m_Columns[3][0]);
    float c2 = (m_Columns[2][0] * m_Columns[3][3]) - (m_Columns[2][3] * m_Columns[3][0]);
    float c3 = (m_Columns[2][1] * m_Columns[3][2]) - (m_Columns[2][2] * m_Columns[3][1]);
    float c4 = (m_Columns[2][1] * m_Columns[3][3]) - (m_Columns[2][3] * m_Columns[3][1]);
    float c5 = (m_Columns[2][2] * m_Columns[3][3]) - (m_Columns[2][3] * m_Columns[3][2]);

    // calculate determinant of 4x4 from submatrices
    float determinant = (s0 * c5) - (s1 * c4) + (s2 * c3) + (s3 * c2) - (s4 * c1) + (s5 * c0);
    if (determinant == 0.f) // avoid divide by 0
        return Identity();
    
    // Get adjudate matrix = transpose of cofactor
    Vector4 adj0 = Vector4(
         (m_Columns[1][1] * c5) - (m_Columns[1][2] * c4) + (m_Columns[1][3] * c3),
        -(m_Columns[0][1] * c5) + (m_Columns[0][2] * c4) - (m_Columns[0][3] * c3),
         (m_Columns[3][1] * s5) - (m_Columns[3][2] * s4) + (m_Columns[3][3] * s3),
        -(m_Columns[2][1] * s5) + (m_Columns[2][2] * s4) - (m_Columns[2][3] * s3)
    );

    Vector4 adj1 = Vector4(
        -(m_Columns[1][0] * c5) + (m_Columns[1][2] * c2) - (m_Columns[1][3] * c1),
         (m_Columns[0][0] * c5) - (m_Columns[0][2] * c2) + (m_Columns[0][3] * c1),
        -(m_Columns[3][0] * s5) + (m_Columns[3][2] * s2) - (m_Columns[3][3] * s1),
         (m_Columns[2][0] * s5) - (m_Columns[2][2] * s2) + (m_Columns[2][3] * s1)
    );

    Vector4 adj2 = Vector4(
         (m_Columns[1][0] * c4) - (m_Columns[1][1] * c2) + (m_Columns[1][3] * c0),
        -(m_Columns[0][0] * c4) + (m_Columns[0][1] * c2) - (m_Columns[0][3] * c0),
         (m_Columns[3][0] * s4) - (m_Columns[3][1] * s2) + (m_Columns[3][3] * s0),
        -(m_Columns[2][0] * s4) + (m_Columns[2][1] * s2) - (m_Columns[2][3] * s0)
    );

    Vector4 adj3 = Vector4(
        -(m_Columns[1][0] * c3) + (m_Columns[1][1] * c1) - (m_Columns[1][2] * c0),
         (m_Columns[0][0] * c3) - (m_Columns[0][1] * c1) + (m_Columns[0][2] * c0),
        -(m_Columns[3][0] * s3) + (m_Columns[3][1] * s1) - (m_Columns[3][2] * s0),
         (m_Columns[2][0] * s3) - (m_Columns[2][1] * s1) + (m_Columns[2][2] * s0)
    );

    // Multiply adj by 1/det for inverse
    float invDet = 1.f / determinant;
    return Matrix4x4(adj0, adj1, adj2, adj3) * invDet;
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

Matrix4x4 Matrix4x4::operator*(float s) const
{
    return Matrix4x4(m_Columns[0] * s, m_Columns[1] * s, m_Columns[2] * s, m_Columns[3] * s);
}

Matrix4x4 & Matrix4x4::operator*=(float s)
{
    m_Columns[0] *= s;
    m_Columns[1] *= s;
    m_Columns[2] *= s;
    m_Columns[3] *= s;

    return *this;
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
    return (m_Columns[0] != m[0]) || (m_Columns[1] != m[1]) || (m_Columns[2] != m[2]) || (m_Columns[3] != m[3]);
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
    // equation used: https://automaticaddison.com/wp-content/uploads/2020/09/quaternion-to-rotation-matrix.jpg
    // source: https://automaticaddison.com/how-to-convert-a-quaternion-to-a-rotation-matrix/
    Vector4 col0(
        (2 * ((q.x * q.x) + (q.w * q.w))) - 1,
         2 * ((q.x * q.y) + (q.w * q.z)),
         2 * ((q.x * q.z) - (q.w * q.y)),
         0
    );

    Vector4 col1(
         2 * ((q.y * q.x) - (q.w * q.z)),
        (2 * ((q.y * q.y) + (q.w * q.w))) - 1,
         2 * ((q.y * q.z) + (q.w * q.x)),
         0
    );

    Vector4 col2(
         2 * ((q.z * q.x) + (q.w * q.y)),
         2 * ((q.z * q.y) - (q.w * q.x)),
        (2 * ((q.z * q.z) + (q.w * q.w))) - 1,
        0
    );

    Vector4 col3(0, 0, 0, 1);

    return Matrix4x4(col0, col1, col2, col3);
}

Matrix4x4 Matrix4x4::Orthographic(const Vector3 & vMin, const Vector3 & vMax)
{
    // equation source: http://www.songho.ca/opengl/gl_projectionmatrix.html#ortho
    Vector3 sum = vMin + vMax;
    Vector3 diff = vMax - vMin;

    Vector4 col0(
        2 / diff.x,
        0, 0, 0
    );

    Vector4 col1(
        0,
        2 / diff.y,
        0, 0
    );

    Vector4 col2(
        0, 0,
        -2 / diff.z,
        0
    );

    Vector4 col3(
        -(sum.x / diff.x),
        -(sum.y / diff.y),
        -(sum.z / diff.z),
        1
    );

    return Matrix4x4(col0, col1, col2, col3);
}

Matrix4x4 Matrix4x4::Perspective(float fov, float width, float height, float near, float far)
{
    assert(near != 0.f);
    float tanFov = tanf(fov * 0.5f);

    Vector4 col0(
        1 / tanFov,
        0, 0, 0
    );

    Vector4 col1(
        0,
        width / (height * tanFov),
        0, 0
    );

    Vector4 col2(
        0, 0,
        (far + near) / (near - far),
        -1
    );

    Vector4 col3(
        0, 0,
        (2 * far * near) / (near - far),
        0
    );

    return Matrix4x4(col0, col1, col2, col3);
}