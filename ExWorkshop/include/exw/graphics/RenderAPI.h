// ;
#pragma once

#include "exw\Common.h"

#include "exw\graphics\VertexArray.h"
#include "exw\maths\matrix4.h"

namespace exw
{
    namespace graphics
    {
        class RenderAPI
        {
        public:
            enum class API
            {
                None = 0,
                OpenGL = 1,
                DirectX = 2,
                Vulkan = 3,
            };

        public:
            virtual ~RenderAPI() = default;

        public:
            virtual void init() = 0;
            virtual void clear() = 0;
            virtual void draw_indexed(const refs::ref<VertexArray>& _vertexArray, uint32_t _indexCount = 0U) = 0;

            virtual void set_viewport(uint32_t _x, uint32_t _y, uint32_t _w, uint32_t _h) = 0;
            virtual void set_clear_color(const maths::vector4& _color) = 0;

            static API get() { return s_API; }

            static API set(API _api) { s_API = _api; }

            static refs::scope<RenderAPI> create();

        private:
            static API s_API;
        };
    }
}
