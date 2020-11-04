// ;
#pragma once

#include "exw\maths\matrix4.h"

namespace exw
{
    class Camera
    {
    public:
        Camera() = default;
        Camera(const maths::matrix4& _projection) : m_Projection(_projection) {}
        virtual ~Camera() = default;

    public:
        const maths::matrix4& get_projection() const { return m_Projection; }

    public:
        enum class ProjectionType
        {
            Orthographic = 1,
            Perspective = 2,
        };
    protected:
        maths::matrix4 m_Projection = maths::matrix4(1.0f);
    };
}
