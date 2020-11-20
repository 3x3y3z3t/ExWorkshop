// ;
#pragma once

#include <glm\vec3.hpp>

namespace exw
{
    namespace maths
    {
        struct vector2;
        struct vector4;

        struct vector3
        {
            union
            {
                glm::vec3 raw;
                struct { float x; float y; float z; };
                struct { float r; float g; float b; };
            };

            vector3();
            vector3(float _x, float _y, float _z);
            vector3(float _scalar);
            vector3(const vector2& _vct);
            vector3(const vector3& _vct);
            vector3(const vector4& _vct);
            vector3(const glm::vec3& _raw);

            float length() { return (float)raw.length(); }


            vector3& operator+=(const vector3& _other) { this->raw += _other.raw; return *this; }
            vector3& operator-=(const vector3& _other) { this->raw -= _other.raw; return *this; }
            vector3& operator*=(const vector3& _other) { this->raw *= _other.raw; return *this; }
            vector3& operator/=(const vector3& _other) { this->raw /= _other.raw; return *this; }

            vector3& operator+=(float _scalar) { this->raw += _scalar; return *this; }
            vector3& operator-=(float _scalar) { this->raw -= _scalar; return *this; }
            vector3& operator*=(float _scalar) { this->raw *= _scalar; return *this; }
            vector3& operator/=(float _scalar) { this->raw /= _scalar; return *this; }

            bool operator== (const vector3& _other) { return raw == _other.raw; }
            bool operator!= (const vector3& _other) { return !(*this == _other); }
            bool operator== (const vector4& _other);
            bool operator!= (const vector4& _other) { return !(*this == _other); }


            friend vector3 operator+(const vector3& _vct1, const vector3& _vct2) { return vector3(_vct1.raw + _vct2.raw); }
            friend vector3 operator-(const vector3& _vct1, const vector3& _vct2) { return vector3(_vct1.raw - _vct2.raw); }
            friend vector3 operator*(const vector3& _vct1, const vector3& _vct2) { return vector3(_vct1.raw * _vct2.raw); }
            friend vector3 operator/(const vector3& _vct1, const vector3& _vct2) { return vector3(_vct1.raw / _vct2.raw); }

            friend vector3 operator+(const vector3& _vct, float _scalar) { return vector3(_vct.raw + _scalar); }
            friend vector3 operator-(const vector3& _vct, float _scalar) { return vector3(_vct.raw - _scalar); }
            friend vector3 operator*(const vector3& _vct, float _scalar) { return vector3(_vct.raw * _scalar); }
            friend vector3 operator/(const vector3& _vct, float _scalar) { return vector3(_vct.raw / _scalar); }

            friend vector3 operator+(float _scalar, const vector3& _vct) { return (_vct + _scalar); }
            friend vector3 operator-(float _scalar, const vector3& _vct) { return (_vct - _scalar); }
            friend vector3 operator*(float _scalar, const vector3& _vct) { return (_vct * _scalar); }
            friend vector3 operator/(float _scalar, const vector3& _vct) { return (_vct / _scalar); }

            friend bool operator==(const vector3& _vct1, const vector3& _vct2) { return _vct1.raw == _vct2.raw; }
            friend bool operator!=(const vector3& _vct1, const vector3& _vct2) { return !(_vct1 == _vct2); }
            friend bool operator==(const vector3& _vct1, const vector4& _vct2);
            friend bool operator!=(const vector3& _vct1, const vector4& _vct2) { return !(_vct1 == _vct2); }

            std::string to_string(bool _longString = false) const
            {
                std::stringstream ss;
                if (_longString)
                    ss << "vector3";
                ss << "(" << x << ", " << y << ", " << z << ")";
                return ss.str();
            }
        };
    }
}
