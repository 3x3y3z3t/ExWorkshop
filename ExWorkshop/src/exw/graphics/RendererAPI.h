/*  RendererAPI.h
*   Version: 1.0 (2022.08.24)
*
*   Contributor
*       Arime-chan
*/
#pragma once

#include "VertexArray.h"

#include "exw\Common.h"
#include "exw\maths\Maths.h"

namespace exw
{
    namespace graphics
    {
        class RendererAPI
        {
        public:
            enum class API : uint8_t
            {
                None = 0,
                OpenGL = 1,
                DirectX = 2,
                Vulkan = 3,
            };

        public:
            virtual ~RendererAPI() = default;

            static refs::Scoped<RendererAPI> create();

            virtual void init() = 0;

            virtual void clear() = 0;
            virtual void draw_indexed(const refs::Ref<VertexArray> _vertexArray, uint32_t _indexCount = 0U) = 0;
            virtual void draw_lines(const refs::Ref<VertexArray> _vertexArray, uint32_t _vertexCount) = 0;

            virtual void set_viewport(uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height) = 0;
            virtual void set_clear_color(maths::vector4 _color) = 0;
            virtual void set_line_width(float _width) = 0;

            static API get_active_api() { return s_Active_api; }
            static void set_active_api(API _api) { s_Active_api = _api; }

        private:
            static API s_Active_api;
        };

    }
}
