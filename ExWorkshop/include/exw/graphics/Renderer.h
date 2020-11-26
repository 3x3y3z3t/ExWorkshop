// ;
#pragma once

#include "RenderAPI.h"
#include "VertexArray.h"
#include "Shader.h"

#include "exw\maths\matrix4.h"

namespace exw
{
    namespace graphics
    {
        class Renderer
        {
        public:
            static void init();
            static void shutdown();

            static void end_scene();
            static void submit(const refs::ref<Shader>& _shader, const refs::ref<VertexArray>& _vertexArray, const maths::matrix4& _transform = maths::matrix4(1.0f));

            static void on_window_resize(uint32_t _width, uint32_t _height);

            static RenderAPI::API get_render_api() { return RenderAPI::get(); }

            static void set_render_api(RenderAPI::API _api) { RenderAPI::set(_api); }

        private:
            struct SceneData
            {
                maths::matrix4 ViewProjectionMatrix;
            };

            static refs::scope<SceneData> s_Scene_data;
        };

        class RenderCommand
        {
        public:
            static void init() { s_Render_api->init(); }
            static void clear() { s_Render_api->clear(); }
            static void draw_indexed(const refs::ref<VertexArray>& _vertexArray, uint32_t _indexCount = 0) { s_Render_api->draw_indexed(_vertexArray, _indexCount); }

            static void set_viewport(uint32_t _x, uint32_t _y, uint32_t _w, uint32_t _h) { s_Render_api->set_viewport(_x, _y, _w, _h); }
            static void set_clear_color(const maths::vector4& _color) { s_Render_api->set_clear_color(_color); }

        private:
            static refs::scope<RenderAPI> s_Render_api;
        };
    }
}
