/*  Camera.h
*   Version: 1.0 (2022.07.26)
*
*   Contributor
*       Arime-chan
*/
#pragma once

#include "exw\maths\Maths.h"

namespace exw
{
    namespace graphics
    {
        class Camera
        {
        public:
            Camera() = default;
            Camera(const maths::matrix4& _projectionMatrix)
                : m_Projection_matrix(_projectionMatrix)
            {}
            virtual ~Camera() = default;

            const maths::matrix4 get_projection_matrix() const { return m_Projection_matrix; }

        protected:
            maths::matrix4 m_Projection_matrix = maths::matrix4(1.0f);
        };

        class OrthographicCamera : public Camera
        {
        public:
            OrthographicCamera(float _left, float _right, float _bottom, float _top);
            virtual ~OrthographicCamera() = default;

            void set_projection(float _left, float _right, float _bottom, float _top);

            const maths::vector3& get_position() const { return m_Position; }
            float get_rotation() const { return m_Rotation; }
            const maths::matrix4& get_view_matrix() const { return m_View_matrix; }
            const maths::matrix4& get_view_projection_matrix() const { return m_View_projection_matrix; }

            void set_position(const maths::vector3& _position) { m_Position = _position; recalculate_view_matrix(); }
            void set_rotation(float _rotation) { m_Rotation = _rotation; recalculate_view_matrix(); }
        private:
            void recalculate_view_matrix();

        private:
            maths::matrix4 m_View_matrix = maths::matrix4(1.0f);
            maths::matrix4 m_View_projection_matrix = maths::matrix4(0.0f);

            maths::vector3 m_Position = maths::vector3(0.0f);
            float m_Rotation = 0.0f;
        };

    }
}
