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
            EXW_PROFILE_FUNCTION();
            exw::graphics::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 1.0f });
        }

        virtual void detach()
        {
            EXW_PROFILE_FUNCTION();

        }

        virtual void update(exw::Timestep _ts) override
        {
            EXW_PROFILE_FUNCTION();
            {
                using namespace exw;


            }

            {
                EXW_PROFILE_SCOPE("Sandbox Rendering");
                using namespace exw;
                using namespace exw::graphics;

                RenderCommand::clear();

                OrthographicCamera cam = OrthographicCamera(-16.0f, 16.0f, -9.0f, 9.0f);

                Renderer2D::begin_scene(cam);


                //Renderer2D::draw_quad({ 2.0f, 2.0f, 0.0f }, { 0.5f, 0.5f }, { 0.0, 1.0f, 1.0f, 1.0f });


                constexpr float xm = 16.0f;
                constexpr float ym = 9.0f;

                constexpr float step = 0.25f;

                constexpr float size = 0.22f;


                for (float y = -ym; y <= ym; y += step)
                {
                    for (float x = -xm; x <= xm; x += step)
                    {
                        exw::maths::vector4 color = {
                            exw::utils::RNG32::next_float(),
                            exw::utils::RNG32::next_float(),
                            exw::utils::RNG32::next_float(),
                            exw::utils::RNG32::next_float(),
                        };
                        Renderer2D::draw_quad({ x, y, 0.0f }, { size, size }, { 0.5f ,0.5f, 0.5f, 1.0f });
                        //Renderer2D::draw_quad({ x, y, 0.0f }, { size, size }, color);
                    }
                }





                refs::ref<Texture2D> kingPcsTexture = Texture2D::create("res/img/chessu/70px_2_1.png");

                //Renderer2D::draw_quad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, kingPcsTexture);


                Renderer2D::end_scene();


            }







        }

        virtual void render_gui() override
        {
            EXW_PROFILE_FUNCTION();
        }

        virtual void on_event(exw::event::Event& _event) override
        {
            EXW_PROFILE_FUNCTION();
        }
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
