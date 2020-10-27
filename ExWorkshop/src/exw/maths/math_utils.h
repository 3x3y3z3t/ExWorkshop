// temporary name;
#pragma once

#include "matrix4.h"
#include "vector3.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
//#include <glm\gtx\transform.hpp>

namespace exw
{
    namespace maths
    {
        static float to_radians(float _degrees) { return float(_degrees * 0.01745329251994329576923690768489); }
        static float to_degrees(float _radians) { return float(_radians * 57.295779513082320876798154814105); }

        static float sin(float _radians) { return glm::sin(_radians); }
        static float cos(float _radians) { return glm::cos(_radians); }
        static float atan(float _y, float _x) { return glm::atan(_y, _x); }

        static float sqrt(float _value) { return glm::sqrt(_value); }
        static float pow(float _base, float _power) { return glm::pow(_base, _power); }

        static float wrap_angle_deg(float _deg)
        {
            if (_deg > 180.0f) return _deg - 360.0f;
            if (_deg < -179.0f) return _deg + 360.0f;
            return _deg;
        }
        template <typename T>
        inline static T sign(T _t) { if (_t > 0) return 1; if (_t < 0) return -1; return 0; }

        static matrix4 orthographics(float _left, float _right, float _bottom, float _top, float _near, float _far)
        {
            return matrix4(glm::ortho(_left, _right, _bottom, _top, _near, _far));
        }

        static matrix4 translate(const matrix4& _mat, const vector3& _axis)
        {
            return matrix4(glm::translate(_mat.raw, _axis.raw));
        }

        static matrix4 rotate(const matrix4& _mat, float _angle, const vector3& _axis)
        {
            return matrix4(glm::rotate(_mat.raw, _angle, _axis.raw));
        }

        static matrix4 scale(const matrix4& _mat, const vector3& _axis)
        {
            return matrix4(glm::scale(_mat.raw, _axis.raw));
        }
    }
}
