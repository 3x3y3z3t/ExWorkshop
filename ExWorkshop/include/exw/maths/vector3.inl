// ;

namespace exw
{
    namespace maths
    {
        inline vector3::vector3() : x(0.0f), y(0.0f), z(0.0f) {}
        inline vector3::vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
        inline vector3::vector3(float _scalar) : x(_scalar), y(_scalar), z(_scalar) {}
        inline vector3::vector3(const vector3& _vct) : x(_vct.x), y(_vct.y), z(_vct.z) {}
        inline vector3::vector3(const glm::vec3& _raw) : raw(_raw) {}

        inline float vector3::length() { return (float)raw.length(); }

        inline vector3& vector3::operator += (const vector3& _other) { this->raw += _other.raw; return *this; }
        inline vector3& vector3::operator -= (const vector3& _other) { this->raw -= _other.raw; return *this; }
        inline vector3& vector3::operator *= (const vector3& _other) { this->raw *= _other.raw; return *this; }
        inline vector3& vector3::operator/=(const vector3& _other) { this->raw /= _other.raw; return *this; }

        inline vector3& vector3::operator+=(float _scalar) { this->raw += _scalar; return *this; }
        inline vector3& vector3::operator-=(float _scalar) { this->raw -= _scalar; return *this; }
        inline vector3& vector3::operator*=(float _scalar) { this->raw *= _scalar; return *this; }
        inline vector3& vector3::operator/=(float _scalar) { this->raw /= _scalar; return *this; }

        inline bool vector3::operator==(const vector3& _other) { return raw == _other.raw; }
        inline bool vector3::operator!=(const vector3& _other) { return !(*this == _other); }
        inline bool vector3::operator!=(const vector4& _other) { return !(*this == _other); }

        inline vector3& vector3::operator-() { x = -x; y = -y; z = -z; return *this; }

        inline vector3 operator+(const vector3& _vct1, const vector3& _vct2) { return vector3(_vct1.raw + _vct2.raw); }
        inline vector3 operator-(const vector3& _vct1, const vector3& _vct2) { return vector3(_vct1.raw - _vct2.raw); }
        inline vector3 operator*(const vector3& _vct1, const vector3& _vct2) { return vector3(_vct1.raw * _vct2.raw); }
        inline vector3 operator/(const vector3& _vct1, const vector3& _vct2) { return vector3(_vct1.raw / _vct2.raw); }

        inline vector3 operator+(const vector3& _vct, float _scalar) { return vector3(_vct.raw + _scalar); }
        inline vector3 operator-(const vector3& _vct, float _scalar) { return vector3(_vct.raw - _scalar); }
        inline vector3 operator*(const vector3& _vct, float _scalar) { return vector3(_vct.raw * _scalar); }
        inline vector3 operator/(const vector3& _vct, float _scalar) { return vector3(_vct.raw / _scalar); }

        inline vector3 operator+(float _scalar, const vector3& _vct) { return vector3(_vct + _scalar); }
        inline vector3 operator-(float _scalar, const vector3& _vct) { return vector3(_vct - _scalar); }
        inline vector3 operator*(float _scalar, const vector3& _vct) { return vector3(_vct * _scalar); }
        inline vector3 operator/(float _scalar, const vector3& _vct) { return vector3(_vct / _scalar); }

        inline bool operator==(const vector3& _vct1, const vector3& _vct2) { return _vct1.raw == _vct2.raw; }
        inline bool operator!=(const vector3& _vct1, const vector3& _vct2) { return !(_vct1 == _vct2); }
        inline bool operator==(const vector3& _vct1, const vector4& _vct2);
        inline bool operator!=(const vector3& _vct1, const vector4& _vct2) { return !(_vct1 == _vct2); }

        //friend vector3 operator-(const vector3& _vct) { return vector3 {-_vct.x, -_vct.y, -_vct.z}; }
    }
}
