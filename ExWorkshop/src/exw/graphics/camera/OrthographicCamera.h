// ;
#pragma once

#include "Camera.h"

#include "exw\maths\matrix4.h"
#include "exw\maths\vector3.h"

namespace exw
{
    namespace graphics
    {
        class __declspec(deprecated) OrthographicCamera : public Camera
        {
        public:
            OrthographicCamera(float _left, float _right, float _bottom, float _top);

        public:
            void set_projection(float _left, float _right, float _bottom, float _top);

            const maths::vector3& get_position() const { return m_Position; }
            float get_rotation() const { return m_Rotation; }

            const maths::matrix4& get_proj_matrix() const { return m_Proj_matrix; }
            const maths::matrix4& get_view_matrix() const { return m_View_matrix; }
            const maths::matrix4& get_view_proj_matrix() const { return m_View_proj_matrix; }

            void set_position(const maths::vector3& _position) { m_Position = _position; update_view_proj_matrix(); }
            void set_rotation(float _rotation) { m_Rotation = _rotation; update_view_proj_matrix(); }
        private:
            void update_view_proj_matrix();

        private:
            maths::matrix4 m_Proj_matrix;
            maths::matrix4 m_View_matrix;
            maths::matrix4 m_View_proj_matrix;

            maths::vector3 m_Position = { 0.0f, 0.0f, 0.0f };
            float m_Rotation = 0.0f;
        };
    }
}
