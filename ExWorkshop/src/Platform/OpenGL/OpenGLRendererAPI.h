/*  OpenGLRendererAPI.h
*   Version: 1.0 (2022.07.24)
*
*   Contributor
*       Arime-chan
*/
#pragma once

#include "exw\graphics\Renderer.h"
#include "exw\graphics\VertexArray.h"

namespace exw
{
    namespace graphics
    {
        class OpenGLRendererAPI : public RendererAPI
        {
        public:
            virtual void init() override;

            virtual void clear() override;
            virtual void draw_indexed(const refs::Ref<VertexArray> _vertexArray, uint32_t _indexCount = 0U) override;
            virtual void draw_lines(const refs::Ref<VertexArray> _vertexArray, uint32_t _vertexCount) override;

            virtual void set_viewport(uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height) override;
            virtual void set_clear_color(maths::vector4 _color) override;
            virtual void set_line_width(float _width) override;
        };

    }
}
