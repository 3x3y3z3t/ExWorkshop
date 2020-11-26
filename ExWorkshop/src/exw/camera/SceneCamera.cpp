// ;
#include "expch.h"
#include "exw\camera\SceneCamera.h"

#include "exw\maths\math_utils.h"

namespace exw
{
    SceneCamera::SceneCamera()
    {
        refresh_projection();
    }

    void SceneCamera::set_viewport_size(uint32_t _width, uint32_t _height)
    {
        m_Orthographic_size = (float)((_width < _height) ? _width : _height);
        float aspectRatio = (float)_width / (float)_height;
        //if (aspectRatio != m_Aspect_ratio)
        {
            m_Aspect_ratio = aspectRatio;
            refresh_projection();
        }
    }

    void SceneCamera::set_orthographic(float _size, float _nearClip, float _farClip)
    {
        m_Projection_type = ProjectionType::Orthographic;
        m_Orthographic_size = _size;
        m_Orthographic_near = _nearClip;
        m_Orthographic_far = _farClip;
        refresh_projection();
    }

    void SceneCamera::set_perspective(float _verticalFov, float _nearClip, float _farClip)
    {
        m_Projection_type = ProjectionType::Perspective;
        m_Perspective_fov = _verticalFov;
        m_Perspective_near = _nearClip;
        m_Perspective_far = _farClip;
        refresh_projection();
    }

    void SceneCamera::refresh_projection()
    {
        if (m_Projection_type == ProjectionType::Orthographic)
        {
            // we are using vertical FoV;
            float orthoL = -m_Orthographic_size * m_Aspect_ratio * 0.5f;
            float orthoR = +m_Orthographic_size * m_Aspect_ratio * 0.5f;
            float orthoB = -m_Orthographic_size * 0.5f;
            float orthoT = +m_Orthographic_size * 0.5f;
            m_Projection = maths::orthographic(orthoL, orthoR, orthoB, orthoT, m_Orthographic_near, m_Orthographic_far);
        }
        else
        {
            m_Projection = maths::perspective(m_Perspective_fov, m_Aspect_ratio, m_Perspective_near, m_Perspective_far);
        }
    }
}
