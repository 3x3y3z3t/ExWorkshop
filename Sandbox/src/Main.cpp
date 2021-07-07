// ;
#include <ExWorkshop.h>
#include <exw\EntryPoint.h>

class Sandbox : public exw::Application
{
public:
    Sandbox()
        :Application("Sandbox")
    {

    }

    ~Sandbox() {}
};

exw::Application* exw::create_application()
{
    return new Sandbox();
}
