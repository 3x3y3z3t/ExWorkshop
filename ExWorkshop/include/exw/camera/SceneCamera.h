// ;
#pragma once

#include "exw\Common.h"
#include "Camera.h"

#include "exw\maths\math_utils.h"

namespace exw
{
    class SceneCamera : public Camera
    {
    public:
        SceneCamera();
        virtual ~SceneCamera() = default;

    public:
        void set_viewport_size(uint32_t _width, uint32_t _height);

        void set_orthographic(float _size, float _nearClip, float _farClip);
        void set_perspective(float _verticalFov, float _nearClip, float _farClip);

        ProjectionType get_projection_type() const { return m_Projection_type; }
        float get_orthographic_size() const { return m_Orthographic_size; }
        float get_orthographic_near_clip() const { return m_Orthographic_near; }
        float get_orthographic_far_clip() const { return m_Orthographic_far; }
        float get_perspective_vertical_fov() const { return m_Perspective_fov; }
        float get_perspective_near_clip() const { return m_Perspective_near; }
        float get_perspective_far_clip() const { return m_Perspective_far; }

        void set_projection_type(ProjectionType _projectionType) { m_Projection_type = _projectionType; refresh_projection(); }
        void set_orthographic_size(float _size) { m_Orthographic_size = _size; refresh_projection(); }
        void set_orthographic_near_clip(float _nearClip) { m_Orthographic_near = _nearClip; }
        void set_orthographic_far_clip(float _farClip) { m_Orthographic_far = _farClip; }
        void set_perspective_vertical_fov(float _fov) { m_Perspective_fov = _fov; }
        void set_perspective_near_clip(float _nearClip) { m_Perspective_near = _nearClip; }
        void set_perspective_far_clip(float _farClip) { m_Perspective_far = _farClip; }
    private:
        void refresh_projection();

    private:
        ProjectionType m_Projection_type = ProjectionType::Orthographic;

        float m_Orthographic_size = 10.0f;
        float m_Orthographic_near = -1.0f;
        float m_Orthographic_far = 1.0f;

        float m_Perspective_fov = maths::to_radians(45.0f);
        float m_Perspective_near = 0.01f;
        float m_Perspective_far = 1000.0f;

        float m_Aspect_ratio = 0.0f;
    };
}
