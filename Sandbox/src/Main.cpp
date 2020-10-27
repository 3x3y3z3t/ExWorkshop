// ;
#include <ExWorkshop.h>
#include <exw\EntryPoint.h>

namespace sb
{
    class SbLayer : public exw::Layer
    {
    public:
        SbLayer()
            : Layer("sb_layer")
        {}

        void on_event(exw::event::Event& _event) override
        {}

        void update(exw::Timestep _ts) override
        {

            {
                using namespace exw;

                maths::vector2 d1(1.0f, 2.0f);
                maths::vector2 d2(2.0f, 3.0f);


                //EXW_LOG_DEBUG("{0}", (d1 + d2).to_string());



            }







        }

        void render_gui() override
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


        EXW_LOG_INFO("Hello from Sandbox");



    }

    ~Sandbox() {}
};

exw::Application* exw::create_application()
{
    return new Sandbox();
}
