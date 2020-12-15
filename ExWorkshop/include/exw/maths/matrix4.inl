// ;

namespace exw
{
    namespace maths
    {
        inline matrix4::matrix4(float _identity) : raw(_identity) {}
        inline matrix4::matrix4(const matrix4& _matrix) : raw(_matrix.raw) {}
        inline matrix4::matrix4(const glm::mat4& _raw) : raw(_raw) {}

        inline const matrix4& matrix4::invert() { raw = glm::inverse(raw);  return *this; }

        inline const vector4& matrix4::operator[](uint8_t _index) { return columns[_index]; }

        inline matrix4 operator*(const matrix4& _mat1, const matrix4& _mat2) { return matrix4(_mat1.raw * _mat2.raw); }
        inline vector4 operator*(const matrix4& _mat1, const vector4& _vec1) { return vector4(_mat1.raw * _vec1.raw); }
    }
}
