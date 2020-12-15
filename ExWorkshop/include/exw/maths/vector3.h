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

            float length();

            vector3& operator+=(const vector3& _other);
            vector3& operator-=(const vector3& _other);
            vector3& operator*=(const vector3& _other);
            vector3& operator/=(const vector3& _other);

            vector3& operator+=(float _scalar);
            vector3& operator-=(float _scalar);
            vector3& operator*=(float _scalar);
            vector3& operator/=(float _scalar);

            bool operator==(const vector3& _other);
            bool operator!=(const vector3& _other);
            bool operator==(const vector4& _other);
            bool operator!=(const vector4& _other);

            vector3& operator-();

            friend vector3 operator+(const vector3& _vct1, const vector3& _vct2);
            friend vector3 operator-(const vector3& _vct1, const vector3& _vct2);
            friend vector3 operator*(const vector3& _vct1, const vector3& _vct2);
            friend vector3 operator/(const vector3& _vct1, const vector3& _vct2);

            friend vector3 operator+(const vector3& _vct, float _scalar);
            friend vector3 operator-(const vector3& _vct, float _scalar);
            friend vector3 operator*(const vector3& _vct, float _scalar);
            friend vector3 operator/(const vector3& _vct, float _scalar);

            friend vector3 operator+(float _scalar, const vector3& _vct);
            friend vector3 operator-(float _scalar, const vector3& _vct);
            friend vector3 operator*(float _scalar, const vector3& _vct);
            friend vector3 operator/(float _scalar, const vector3& _vct);

            std::string to_string(bool _longString = false) const;

            friend bool operator==(const vector3& _vct1, const vector3& _vct2);
            friend bool operator!=(const vector3& _vct1, const vector3& _vct2);
            friend bool operator==(const vector3& _vct1, const vector4& _vct2);
            friend bool operator!=(const vector3& _vct1, const vector4& _vct2);

            //friend vector3 operator-(const vector3& _vct) { return vector3 {-_vct.x, -_vct.y, -_vct.z}; }
        };
    }
}

#include "vector3.inl"
