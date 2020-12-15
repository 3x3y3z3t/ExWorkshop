// ;

namespace exw
{
    namespace maths
    {
        inline vector4::vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
        inline vector4::vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
        inline vector4::vector4(float _scalar) : x(_scalar), y(_scalar), z(_scalar), w(_scalar) {}
        inline vector4::vector4(const vector4& _vct) : raw(_vct.raw) {}
        inline vector4::vector4(const glm::vec4& _raw) : raw(_raw) {}

        inline float vector4::length() { return (float)raw.length(); }

        inline vector4& vector4::operator+=(const vector4& _other) { this->raw += _other.raw; return *this; }
        inline vector4& vector4::operator-=(const vector4& _other) { this->raw -= _other.raw; return *this; }
        inline vector4& vector4::operator*=(const vector4& _other) { this->raw *= _other.raw; return *this; }
        inline vector4& vector4::operator/=(const vector4& _other) { this->raw /= _other.raw; return *this; }

        inline vector4& vector4::operator+=(float _scalar) { this->raw += _scalar; return *this; }
        inline vector4& vector4::operator-=(float _scalar) { this->raw -= _scalar; return *this; }
        inline vector4& vector4::operator*=(float _scalar) { this->raw *= _scalar; return *this; }
        inline vector4& vector4::operator/=(float _scalar) { this->raw /= _scalar; return *this; }

        inline bool vector4::operator==(const vector4& _other) { return raw == _other.raw; }
        inline bool vector4::operator!=(const vector4& _other) { return !(*this == _other); }
        inline bool vector4::operator!=(const vector3& _other) { return !(*this == _other); }

        inline vector4& vector4::operator-() { x = -x; y = -y; z = -z; w = -w; return *this; }

        inline vector4 operator+(const vector4& _vct1, const vector4& _vct2) { return vector4(_vct1.raw + _vct2.raw); }
        inline vector4 operator-(const vector4& _vct1, const vector4& _vct2) { return vector4(_vct1.raw - _vct2.raw); }
        inline vector4 operator*(const vector4& _vct1, const vector4& _vct2) { return vector4(_vct1.raw * _vct2.raw); }
        inline vector4 operator/(const vector4& _vct1, const vector4& _vct2) { return vector4(_vct1.raw / _vct2.raw); }

        inline vector4 operator+(const vector4& _vct, float _scalar) { return vector4(_vct.raw + _scalar); }
        inline vector4 operator-(const vector4& _vct, float _scalar) { return vector4(_vct.raw - _scalar); }
        inline vector4 operator*(const vector4& _vct, float _scalar) { return vector4(_vct.raw * _scalar); }
        inline vector4 operator/(const vector4& _vct, float _scalar) { return vector4(_vct.raw / _scalar); }

        inline vector4 operator+(float _scalar, const vector4& _vct) { return (_vct + _scalar); }
        inline vector4 operator-(float _scalar, const vector4& _vct) { return (_vct - _scalar); }
        inline vector4 operator*(float _scalar, const vector4& _vct) { return (_vct * _scalar); }
        inline vector4 operator/(float _scalar, const vector4& _vct) { return (_vct / _scalar); }

        inline bool operator==(const vector4& _vct1, const vector4& _vct2) { return _vct1.raw == _vct2.raw; }
        inline bool operator!=(const vector4& _vct1, const vector4& _vct2) { return !(_vct1 == _vct2); }
        inline bool operator==(const vector4& _vct1, const vector3& _vct2);
        inline bool operator!=(const vector4& _vct1, const vector3& _vct2) { return !(_vct1 == _vct2); }
    }
}
