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

            float length();

            vector2& operator+=(const vector2& _other);
            vector2& operator-=(const vector2& _other);
            vector2& operator*=(const vector2& _other);
            vector2& operator/=(const vector2& _other);

            vector2& operator+=(float _scalar);
            vector2& operator-=(float _scalar);
            vector2& operator*=(float _scalar);
            vector2& operator/=(float _scalar);

            bool operator== (const vector2& _other);
            bool operator!= (const vector2& _other);

            vector2& operator-();

            std::string to_string(bool _longString = false) const;

            friend vector2 operator+(const vector2& _vct1, const vector2& _vct2);
            friend vector2 operator-(const vector2& _vct1, const vector2& _vct2);
            friend vector2 operator*(const vector2& _vct1, const vector2& _vct2);
            friend vector2 operator/(const vector2& _vct1, const vector2& _vct2);

            friend vector2 operator+(const vector2& _vct, float _scalar);
            friend vector2 operator-(const vector2& _vct, float _scalar);
            friend vector2 operator*(const vector2& _vct, float _scalar);
            friend vector2 operator/(const vector2& _vct, float _scalar);

            friend vector2 operator+(float _scalar, const vector2& _vct);
            friend vector2 operator-(float _scalar, const vector2& _vct);
            friend vector2 operator*(float _scalar, const vector2& _vct);
            friend vector2 operator/(float _scalar, const vector2& _vct);

            friend bool operator==(const vector2& _vct1, const vector2& _vct2);
            friend bool operator!=(const vector2& _vct1, const vector2& _vct2);
        };
    }
}

#include "vector2.inl"
