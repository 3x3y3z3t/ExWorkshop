/*  Renderer.h
*   Version: 1.0 (2022.08.24)
*
*   Contributor
*       Arime-chan
*/
#pragma once

#include "Camera.h"
#include "RendererAPI.h"
#include "Shader.h"
#include "VertexArray.h"

#include "exw\Common.h"
#include "exw\maths\Maths.h"

namespace exw
{
    namespace graphics
    {
        class Renderer
        {
        public:
            static void init();
            static void shutdown();

            static void begin_scene(OrthographicCamera& _camera);
            static void end_scene();

            static void submit(const refs::Ref<Shader>& _shader, const refs::Ref<VertexArray>& _vertexArray, const maths::matrix4& _transform);

            static void on_window_resize(uint32_t _width, uint32_t _height);

            static RendererAPI::API get_active_api() { return RendererAPI::get_active_api(); }

            #pragma region RenderCommand
            static void clear() { s_Renderer->clear(); }

            static void draw_indexed(const refs::Ref<VertexArray>& _vertexArray, uint32_t _indexCount = 0) { s_Renderer->draw_indexed(_vertexArray, _indexCount); }
            static void draw_lines(const refs::Ref<VertexArray>& _vertexArray, uint32_t _vertexCount) { s_Renderer->draw_lines(_vertexArray, _vertexCount); }

            static void set_viewport(uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height) { s_Renderer->set_viewport(_x, _y, _width, _height); }
            static void set_clear_color(const maths::vector4& _color) { s_Renderer->set_clear_color(_color); }
            static void set_line_width(float _width) { s_Renderer->set_line_width(_width); }
            #pragma endregion

        private:
            struct SceneData { maths::matrix4 ViewProjMatrix; };

            static refs::Scoped<RendererAPI> s_Renderer;
            static refs::Scoped<SceneData> s_Scene_data;
        };

    }
}
