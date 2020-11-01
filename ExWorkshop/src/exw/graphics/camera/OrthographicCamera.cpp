// ;
#include "expch.h"
#include "OrthographicCamera.h"

#include "exw\maths\math_utils.h"

namespace exw
{
    namespace graphics
    {
        OrthographicCamera::OrthographicCamera(float _left, float _right, float _bottom, float _top)
            : m_Proj_matrix(maths::orthographic(_left, _right, _bottom, _top, -1.0f, 1.0f)), m_View_matrix(1.0f)
        {
            m_View_proj_matrix = m_Proj_matrix * m_View_matrix;
        }

        void OrthographicCamera::set_projection(float _left, float _right, float _bottom, float _top)
        {
            m_Proj_matrix = maths::orthographic(_left, _right, _bottom, _top, -1.0f, 1.0f);
            m_View_proj_matrix = m_Proj_matrix * m_View_matrix;
        }

        void OrthographicCamera::update_view_proj_matrix()
        {
            maths::matrix4 transform =
                maths::translate(maths::matrix4(1.0f), m_Position) *
                maths::rotate(maths::matrix4(1.0f), maths::to_radians(m_Rotation), { 0.0f, 0.0f, 1.0f });

            m_View_matrix = transform.invert();
            m_View_proj_matrix = m_Proj_matrix * m_View_matrix;
        }
    }
}
