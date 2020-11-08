// ;
#pragma once

#include <glm\vec2.hpp>

namespace exw
{
    namespace maths
    {
        struct vector3;
        struct vector4;

        struct vector2
        {
            union
            {
                glm::vec2 raw;
                struct { float x; float y; };
            };

            vector2();
            vector2(float _x, float _y);
            vector2(float _scalar);
            vector2(const vector2& _vct);
            vector2(const vector3& _vct);
            vector2(const vector4& _vct);
            vector2(const glm::vec2& _raw);

            float length() { return (float)raw.length(); }


            vector2& operator+=(const vector2& _other) { this->raw += _other.raw; return *this; }
            vector2& operator-=(const vector2& _other) { this->raw -= _other.raw; return *this; }
            vector2& operator*=(const vector2& _other) { this->raw *= _other.raw; return *this; }
            vector2& operator/=(const vector2& _other) { this->raw /= _other.raw; return *this; }

            vector2& operator+=(float _scalar) { this->raw += _scalar; return *this; }
            vector2& operator-=(float _scalar) { this->raw -= _scalar; return *this; }
            vector2& operator*=(float _scalar) { this->raw *= _scalar; return *this; }
            vector2& operator/=(float _scalar) { this->raw /= _scalar; return *this; }

            bool operator== (const vector2& _other) { return raw == _other.raw; }
            bool operator!= (const vector2& _other) { return !(*this == _other); }


            friend vector2 operator+(const vector2& _vct1, const vector2& _vct2) { return vector2(_vct1.raw + _vct2.raw); }
            friend vector2 operator-(const vector2& _vct1, const vector2& _vct2) { return vector2(_vct1.raw - _vct2.raw); }
            friend vector2 operator*(const vector2& _vct1, const vector2& _vct2) { return vector2(_vct1.raw * _vct2.raw); }
            friend vector2 operator/(const vector2& _vct1, const vector2& _vct2) { return vector2(_vct1.raw / _vct2.raw); }

            friend vector2 operator+(const vector2& _vct, float _scalar) { return vector2(_vct.raw + _scalar); }
            friend vector2 operator-(const vector2& _vct, float _scalar) { return vector2(_vct.raw - _scalar); }
            friend vector2 operator*(const vector2& _vct, float _scalar) { return vector2(_vct.raw * _scalar); }
            friend vector2 operator/(const vector2& _vct, float _scalar) { return vector2(_vct.raw / _scalar); }

            friend vector2 operator+(float _scalar, const vector2& _vct) { return (_vct + _scalar); }
            friend vector2 operator-(float _scalar, const vector2& _vct) { return (_vct - _scalar); }
            friend vector2 operator*(float _scalar, const vector2& _vct) { return (_vct * _scalar); }
            friend vector2 operator/(float _scalar, const vector2& _vct) { return (_vct / _scalar); }

            friend bool operator==(const vector2& _vct1, const vector2& _vct2) { return _vct1.raw == _vct2.raw; }
            friend bool operator!=(const vector2& _vct1, const vector2& _vct2) { return !(_vct1 == _vct2); }

            std::string to_string(bool _longString = false) const
            {
                std::stringstream ss;
                if (_longString)
                    ss << "vector2";
                ss << "(" << x << ", " << y << ")";
                return ss.str();
            }
        };
    }
}
