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
        transform.Scale = { 0.5f, 2.0f, 1.0f };

        m_Camera = m_Active_scene->create_entity("Camera");
        auto& cameraComp = m_Camera.add_component<exw::CameraComponent>(true);
        
        class CameraController : public exw::ScriptableEntity
        {
        public:
            virtual void create() override
            {}

            virtual void destroy() override
            {}

            virtual void update(exw::Timestep _ts) override
            {
                auto& translation = get_component<exw::TransformComponent>().Translation;
                auto& rotation = get_component<exw::TransformComponent>().Rotation;

                float speed = 5.0f * 0.001f;

                if (exw::Input::is_key_pressed(exw::Keys::Q))
                    rotation.z -= speed * _ts;
                else if (exw::Input::is_key_pressed(exw::Keys::E))
                    rotation.z += speed * _ts;


                if (exw::Input::is_key_pressed(exw::Keys::A))
                    translation.x -= speed * _ts;
                else if (exw::Input::is_key_pressed(exw::Keys::D))
                    translation.x += speed * _ts;
                if (exw::Input::is_key_pressed(exw::Keys::W))
                    translation.y += speed * _ts;
                else if (exw::Input::is_key_pressed(exw::Keys::S))
                    translation.y -= speed * _ts;
            }
        };


        

        m_Camera.add_component<exw::ScriptComponent>().bind<CameraController>();


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
