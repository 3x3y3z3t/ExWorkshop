// ;
#pragma once

#include <glm\vec4.hpp>

namespace exw
{
    namespace maths
    {
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
            vector4(const vector4& _vct);
            vector4(const glm::vec4& _raw);

            float length() { return (float)raw.length(); }

            vector4& operator+=(const vector4& _other) { this->raw += _other.raw; return *this; }

            bool operator== (const vector4& _other) { return raw == _other.raw; }
            bool operator!= (const vector4& _other) { return !(*this == _other); }

            friend vector4 operator+(const vector4& _vct1, const vector4& _vct2);

            friend bool operator==(const vector4& _vct1, const vector4& _vct2) { return _vct1.raw == _vct2.raw; }
            friend bool operator!=(const vector4& _vct1, const vector4& _vct2) { return !(_vct1 == _vct2); }

            std::string to_string(bool _longString = false) const
            {
                std::stringstream ss;
                if (_longString)
                    ss << "vector4";
                ss << "(" << x << ", " << y << ", " << z << ", " << w << ")";
                return ss.str();
            }
        };
    }
}
