// ;
#pragma once

#include "exw\graphics\RenderAPI.h"
#include "exw\graphics\VertexArray.h"

namespace exw
{
    namespace graphics
    {
        class OpenGLRenderAPI : public RenderAPI
        {
        public:
            virtual void init() override;
            virtual void clear() override;
            virtual void draw_indexed(const refs::ref<VertexArray>& _vertexArray, uint32_t _indexCount = 0) override;

            virtual void set_viewport(uint32_t _x, uint32_t _y, uint32_t _w, uint32_t _h) override;
            virtual void set_clear_color(const maths::vector4& _color) override;
        };
    }
}
