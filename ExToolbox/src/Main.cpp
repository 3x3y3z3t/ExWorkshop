// ;
#include <ExWorkshop.h>
#include <exw\EntryPoint.h>

#include "EditorLayer.h"

class ExToolbox : public exw::Application
{
public:
    ExToolbox()
        : Application("ExToolbox", 1600U, 900U)
    {
        this->get_window().set_vsync(false);


        push_layer(new exw::EditorLayer());





    }

    ~ExToolbox() {}
};

exw::Application* exw::create_application()
{
    return new ExToolbox();
}
