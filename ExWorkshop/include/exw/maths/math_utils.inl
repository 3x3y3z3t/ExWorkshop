// ;

#ifdef EXW_ENABLE_EXPERIMENTAL
    #ifndef GLM_ENABLE_EXPERIMENTAL
        #define GLM_ENABLE_EXPERIMENTAL
    #endif
#endif

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace exw
{
    namespace maths
    {
        template<typename T>
        inline constexpr T sign(T _t)
        {
            if (_t > (T)0) return (T)1;
            if (_t < (T)0) return (T)-1;
            return (T)1;
        }

        template <typename T>
        inline constexpr T min(T _t1, T _t2)
        {
            return std::min(_t1, _t2);
        }

        template <typename T>
        inline constexpr T max(T _t1, T _t2)
        {
            return std::max(_t1, _t2);
        }

        template <typename T>
        inline constexpr T to_radians(T _degrees)
        {
            return _degrees * Pi_over_180d;
        }

        template <typename T>
        inline constexpr T to_degrees(T _radians)
        {
            return _radians * Pi_divides_180d;
        }

        inline constexpr float wrap_angle_deg(float _deg)
        {
            if (_deg > 180.0f) return _deg - 360.0f;
            if (_deg < -179.0f) return _deg + 360.0f;
            return _deg;
        }

        inline constexpr float wrap_angle_rad(float _rad)
        {
            return wrap_angle_deg(to_degrees(_rad));
        }

        inline float sin(float _radians)
        {
            return glm::sin(_radians);
        }

        inline float cos(float _radians)
        {
            return glm::cos(_radians);
        }

        inline float atan(float _y, float _x)
        {
            return glm::atan(_y, _x);
        }

        inline float sqrt(float _value)
        {
            return glm::sqrt(_value);
        }

        inline float pow(float _base, float _power)
        {
            return glm::pow(_base, _power);
        }


    }
}
