// ;

namespace exw
{
    namespace maths
    {
        inline vector2::vector2() : x(0.0f), y(0.0f) {}
        inline vector2::vector2(float _x, float _y) : x(_x), y(_y) {}
        inline vector2::vector2(float _scalar) : x(_scalar), y(_scalar) {}
        inline vector2::vector2(const vector2& _vct) : x(_vct.x), y(_vct.y) {}
        inline vector2::vector2(const glm::vec2& _raw) : raw(_raw) {}

        inline float vector2::length() { return (float)raw.length(); }

        inline vector2& vector2::operator+=(const vector2& _other) { this->raw += _other.raw; return *this; }
        inline vector2& vector2::operator-=(const vector2& _other) { this->raw -= _other.raw; return *this; }
        inline vector2& vector2::operator*=(const vector2& _other) { this->raw *= _other.raw; return *this; }
        inline vector2& vector2::operator/=(const vector2& _other) { this->raw /= _other.raw; return *this; }

        inline vector2& vector2::operator+=(float _scalar) { this->raw += _scalar; return *this; }
        inline vector2& vector2::operator-=(float _scalar) { this->raw -= _scalar; return *this; }
        inline vector2& vector2::operator*=(float _scalar) { this->raw *= _scalar; return *this; }
        inline vector2& vector2::operator/=(float _scalar) { this->raw /= _scalar; return *this; }

        inline bool vector2::operator==(const vector2& _other) { return raw == _other.raw; }
        inline bool vector2::operator!=(const vector2& _other) { return !(*this == _other); }

        inline vector2& vector2::operator-() { x = -x; y = -y; return *this; }

        inline vector2 operator+(const vector2& _vct1, const vector2& _vct2) { return vector2(_vct1.raw + _vct2.raw); }
        inline vector2 operator-(const vector2& _vct1, const vector2& _vct2) { return vector2(_vct1.raw - _vct2.raw); }
        inline vector2 operator*(const vector2& _vct1, const vector2& _vct2) { return vector2(_vct1.raw * _vct2.raw); }
        inline vector2 operator/(const vector2& _vct1, const vector2& _vct2) { return vector2(_vct1.raw / _vct2.raw); }

        inline vector2 operator+(const vector2& _vct, float _scalar) { return vector2(_vct.raw + _scalar); }
        inline vector2 operator-(const vector2& _vct, float _scalar) { return vector2(_vct.raw - _scalar); }
        inline vector2 operator*(const vector2& _vct, float _scalar) { return vector2(_vct.raw * _scalar); }
        inline vector2 operator/(const vector2& _vct, float _scalar) { return vector2(_vct.raw / _scalar); }

        inline vector2 operator+(float _scalar, const vector2& _vct) { return (_vct + _scalar); }
        inline vector2 operator-(float _scalar, const vector2& _vct) { return (_vct - _scalar); }
        inline vector2 operator*(float _scalar, const vector2& _vct) { return (_vct * _scalar); }
        inline vector2 operator/(float _scalar, const vector2& _vct) { return (_vct / _scalar); }

        inline bool operator==(const vector2& _vct1, const vector2& _vct2) { return _vct1.raw == _vct2.raw; }
        inline bool operator!=(const vector2& _vct1, const vector2& _vct2) { return !(_vct1 == _vct2); }
    }
}
