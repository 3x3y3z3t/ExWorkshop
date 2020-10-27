// ;
#pragma once

#include <glm\vec3.hpp>

namespace exw
{
    namespace maths
    {
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
            vector3(const vector3& _vct);
            vector3(const glm::vec3& _raw);

            float length() { return (float)raw.length(); }

            vector3& operator+=(const vector3& _other) { this->raw += _other.raw; return *this; }

            bool operator== (const vector3& _other) { return raw == _other.raw; }
            bool operator!= (const vector3& _other) { return !(*this == _other); }

            friend vector3 operator+(const vector3& _vct1, const vector3& _vct2);

            friend bool operator==(const vector3& _vct1, const vector3& _vct2) { return _vct1.raw == _vct2.raw; }
            friend bool operator!=(const vector3& _vct1, const vector3& _vct2) { return !(_vct1 == _vct2); }

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
