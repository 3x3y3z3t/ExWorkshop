// ;
#include <ExWorkshop.h>
//#include <exw\EntryPoint.h>

namespace sb
{
    class SbLayer : public exw::Layer
    {
    public:
        SbLayer()
            : Layer("sb_layer")
        {}

        virtual void attach()
        {
            exw::graphics::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 1.0f });
        }

        virtual void detach()
        {

        }

        virtual void update(exw::Timestep _ts) override
        {

            {
                using namespace exw;

                maths::vector2 d1(1.0f, 2.0f);
                maths::vector2 d2(2.0f, 3.0f);


                //EXW_LOG_DEBUG("{0}", (d1 + d2).to_string());

            }

            {
                using namespace exw;
                using namespace exw::graphics;

                RenderCommand::clear();


                OrthographicCamera cam = OrthographicCamera(-16.0f, 16.0f, -9.0f, 9.0f);


                Renderer2D::begin_scene(cam);


                Renderer2D::draw_quad({ 2.0f, 2.0f, 0.0f }, { 0.5f, 0.5f }, { 0.0, 1.0f, 1.0f, 1.0f });


                refs::ref<Texture2D> kingPcsTexture = Texture2D::create("res/img/chessu/70px_2_1.png");

                Renderer2D::draw_quad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, kingPcsTexture);


                Renderer2D::end_scene();


            }







        }

        virtual void render_gui() override
        {}

        virtual void on_event(exw::event::Event& _event) override
        {}
    };
}

class Sandbox : public exw::Application
{
public:
    Sandbox()
        : Application("Sandbox", 1600U, 900U)
    {
        this->get_window().set_vsync(false);


        push_layer(new sb::SbLayer());





    }

    ~Sandbox() {}
};

exw::Application* exw::create_application()
{
    return new Sandbox();
}
