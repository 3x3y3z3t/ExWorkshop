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
        {}

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
    }

    ~Sandbox() {}
};

exw::Application* exw::create_application()
{
    return new Sandbox();
}
