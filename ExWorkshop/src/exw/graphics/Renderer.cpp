/*  Renderer.cpp
*   Version: 1.0 (2022.08.24)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "Renderer.h"

namespace exw
{
    namespace graphics
    {
        refs::Scoped<RendererAPI> Renderer::s_Renderer = nullptr;
        refs::Scoped<Renderer::SceneData> Renderer::s_Scene_data = refs::create_scoped<Renderer::SceneData>();

        void Renderer::init()
        {
            //TODO: check before reinit;

            s_Renderer = RendererAPI::create();
            s_Renderer->init();
            //Renderer2D::init();
        }

        void Renderer::shutdown()
        {
            //Renderer2D::shutdown();
        }

        void Renderer::on_window_resize(uint32_t _width, uint32_t _height)
        {
            Renderer::set_viewport(0U, 0U, _width, _height);
        }

        void Renderer::begin_scene(OrthographicCamera& _camera)
        {
            s_Scene_data->ViewProjMatrix = _camera.get_view_projection_matrix();
        }

        void Renderer::end_scene()
        {}

        void Renderer::submit(const refs::Ref<Shader>&_shader, const refs::Ref<VertexArray>&_vertexArray, const maths::matrix4& _transform)
        {
            _shader->bind();
            _shader->set_matrix4("u_ViewProjMat", s_Scene_data->ViewProjMatrix);
            _shader->set_matrix4("u_Transform", _transform);

            _vertexArray->bind();
            Renderer::draw_indexed(_vertexArray);
        }

    }
}
