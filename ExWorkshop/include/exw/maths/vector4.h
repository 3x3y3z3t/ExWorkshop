// ;
#pragma once

#include <glm\vec4.hpp>

namespace exw
{
    namespace maths
    {
        struct vector2;
        struct vector3;

        struct vector4
        {
            union
            {
                glm::vec4 raw;
                struct { float x; float y; float z; float w; };
                struct { float r; float g; float b; float a; };
            };

            vector4();
            vector4(float _x, float _y, float _z, float _w);
            vector4(float _scalar);
            vector4(const vector2& _vct);
            vector4(const vector3& _vct);
            vector4(const vector4& _vct);
            vector4(const glm::vec4& _raw);

            float length();

            vector4& operator+=(const vector4& _other);
            vector4& operator-=(const vector4& _other);
            vector4& operator*=(const vector4& _other);
            vector4& operator/=(const vector4& _other);

            vector4& operator+=(float _scalar);
            vector4& operator-=(float _scalar);
            vector4& operator*=(float _scalar);
            vector4& operator/=(float _scalar);

            bool operator==(const vector4& _other);
            bool operator!=(const vector4& _other);
            bool operator==(const vector3& _other);
            bool operator!=(const vector3& _other);

            vector4& operator-();

            std::string to_string(bool _longString = false) const;

            friend vector4 operator+(const vector4& _vct1, const vector4& _vct2);
            friend vector4 operator-(const vector4& _vct1, const vector4& _vct2);
            friend vector4 operator*(const vector4& _vct1, const vector4& _vct2);
            friend vector4 operator/(const vector4& _vct1, const vector4& _vct2);

            friend vector4 operator+(const vector4& _vct, float _scalar);
            friend vector4 operator-(const vector4& _vct, float _scalar);
            friend vector4 operator*(const vector4& _vct, float _scalar);
            friend vector4 operator/(const vector4& _vct, float _scalar);

            friend vector4 operator+(float _scalar, const vector4& _vct);
            friend vector4 operator-(float _scalar, const vector4& _vct);
            friend vector4 operator*(float _scalar, const vector4& _vct);
            friend vector4 operator/(float _scalar, const vector4& _vct);

            friend bool operator==(const vector4& _vct1, const vector4& _vct2);
            friend bool operator!=(const vector4& _vct1, const vector4& _vct2);
            friend bool operator==(const vector4& _vct1, const vector3& _vct2);
            friend bool operator!=(const vector4& _vct1, const vector3& _vct2);

        };
    }
}

#include "vector4.inl"
