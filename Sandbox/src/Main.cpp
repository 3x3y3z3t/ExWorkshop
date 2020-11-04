// ;
#include <ExWorkshop.h>
#include <exw\EntryPoint.h>

#include "SbLayer.h"

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
