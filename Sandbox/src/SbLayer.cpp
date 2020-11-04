// ;
#include "SbLayer.h"

namespace sb
{
    SbLayer::SbLayer()
        : Layer("sb_layer")
    {}

    void SbLayer::attach()
    {
        EXW_PROFILE_FUNCTION();
        exw::graphics::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 1.0f });

        m_Active_scene = exw::refs::create_ref<exw::Scene>();

        m_Square = m_Active_scene->create_entity("Square");
        m_Square.add_component<exw::SpriteRendererComponent>(exw::maths::vector4 { 0.0f, 1.0f, 1.0f, 1.0f });
        auto& transform = m_Square.get_component<exw::TransformComponent>();

        m_Camera = m_Active_scene->create_entity("Camera");
        auto& cameraComp = m_Camera.add_component<exw::CameraComponent>(true);
        

    }

    void SbLayer::detach()
    {
        EXW_PROFILE_FUNCTION();

    }

    void SbLayer::update(exw::Timestep _ts)
    {
        EXW_PROFILE_FUNCTION();
        m_Active_scene->on_viewport_resize(1600U, 900U);

        {
            using namespace exw;


        }

        {
            EXW_PROFILE_SCOPE("Sandbox Rendering");
            using namespace exw;
            using namespace exw::graphics;

            RenderCommand::clear();

            m_Active_scene->update(_ts);










            OrthographicCamera cam = OrthographicCamera(-16.0f, 16.0f, -9.0f, 9.0f);

            Renderer2D::begin_scene(cam);



            //constexpr float xm = 16.0f;
            //constexpr float ym = 9.0f;

            //constexpr float step = 0.25f;

            //constexpr float size = 0.22f;


            //for (float y = -ym; y <= ym; y += step)
            //{
            //    for (float x = -xm; x <= xm; x += step)
            //    {
            //        exw::maths::vector4 color = {
            //            exw::utils::RNG32::next_float(),
            //            exw::utils::RNG32::next_float(),
            //            exw::utils::RNG32::next_float(),
            //            exw::utils::RNG32::next_float(),
            //        };
            //        Renderer2D::draw_quad({ x, y, 0.0f }, { size, size }, { 0.5f ,0.5f, 0.5f, 1.0f });
            //        //Renderer2D::draw_quad({ x, y, 0.0f }, { size, size }, color);
            //    }
            //}



            //refs::ref<Texture2D> kingPcsTexture = Texture2D::create("res/img/chessu/70px_2_1.png");
            //Renderer2D::draw_quad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, kingPcsTexture);


            Renderer2D::end_scene();


        }

    }

    void SbLayer::render_gui()
    {
        EXW_PROFILE_FUNCTION();
    }

    void SbLayer::on_event(exw::event::Event& _event)
    {
        EXW_PROFILE_FUNCTION();
    }
}
