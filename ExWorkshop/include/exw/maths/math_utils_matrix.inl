// ;

namespace exw
{
    namespace maths
    {
        inline matrix4 inverse(const matrix4& _mat)
        {
            return glm::inverse(_mat.raw);
        }

        inline matrix4 translate(const matrix4& _mat, const vector3& _axis)
        {
            return matrix4(glm::translate(_mat.raw, _axis.raw));
        }

        inline matrix4 rotate(const matrix4& _mat, float _angle, const vector3& _axis)
        {
            return matrix4(glm::rotate(_mat.raw, _angle, _axis.raw));
        }

#ifdef EXW_ENABLE_EXPERIMENTAL
        inline vector3 rotate(const quaternion& _quat, const vector3& _axis)
        {
            return vector3(glm::rotate(_quat.raw, _axis.raw));
        }
#endif

        inline matrix4 scale(const matrix4& _mat, const vector3& _axis)
        {
            return matrix4(glm::scale(_mat.raw, _axis.raw));
        }

        inline matrix4 orthographic(float _left, float _right, float _bottom, float _top, float _near, float _far)
        {
            return matrix4(glm::ortho(_left, _right, _bottom, _top, _near, _far));
        }

        inline matrix4 perspective(float _verticalFov, float _aspectRatio, float _near, float _far)
        {
            return matrix4(glm::perspective(_verticalFov, _aspectRatio, _near, _far));
        }
    }
}
