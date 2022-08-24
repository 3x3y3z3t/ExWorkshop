/*  Camera.cpp
*   Version: 1.0 (2022.07.26)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "Camera.h"

#include <glm\gtc\matrix_transform.hpp>

namespace exw
{
    namespace graphics
    {
        OrthographicCamera::OrthographicCamera(float _left, float _right, float _bottom, float _top)
            : Camera(glm::ortho(_left, _right, _bottom, _top, -1.0f, 1.0f))
        {
            m_View_projection_matrix = m_Projection_matrix * m_View_matrix;
        }

        void OrthographicCamera::set_projection(float _left, float _right, float _bottom, float _top)
        {
            m_Projection_matrix = glm::ortho(_left, _right, _bottom, _top, -1.0f, 1.0f);
            m_View_projection_matrix = m_Projection_matrix * m_View_matrix;
        }

        void OrthographicCamera::recalculate_view_matrix()
        {
            maths::matrix4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

            m_View_matrix = glm::inverse(transform);
            m_View_projection_matrix = m_Projection_matrix * m_View_matrix;
        }
    }
}
