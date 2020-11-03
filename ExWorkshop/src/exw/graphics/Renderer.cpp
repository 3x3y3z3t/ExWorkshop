// ;
#include "expch.h"
#include "Renderer.h"

#include "Renderer2D.h"

namespace exw
{
    namespace graphics
    {
        refs::scope<Renderer::SceneData> Renderer::s_Scene_data = refs::create_scoped<Renderer::SceneData>();

        void Renderer::init()
        {
            EXW_PROFILE_FUNCTION();
            RenderCommand::init();
            Renderer2D::init();
        }

        void Renderer::shutdown()
        {
            Renderer2D::shutdown();
        }

        void Renderer::begin_scene(OrthographicCamera& _camera)
        {
            s_Scene_data->ViewProjectionMatrix = _camera.get_view_proj_matrix();
        }

        void Renderer::end_scene()
        {}

        void Renderer::submit(const refs::ref<Shader>& _shader, const refs::ref<VertexArray>& _vertexArray, const maths::matrix4& _transform)
        {
            _shader->bind();
            _shader->set_uniform_mat4x4("u_ViewProj", s_Scene_data->ViewProjectionMatrix);
            _shader->set_uniform_mat4x4("u_Transform", _transform);

            _vertexArray->bind();
            RenderCommand::draw_indexed(_vertexArray);
        }

        void Renderer::on_window_resize(uint32_t _width, uint32_t _height)
        {
            RenderCommand::set_viewport(0U, 0U, _width, _height);
        }

        refs::scope<RenderAPI> RenderCommand::s_Render_api = RenderAPI::create();
    }
}
