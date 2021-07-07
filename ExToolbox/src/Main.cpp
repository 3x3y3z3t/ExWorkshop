// ;
#include <ExWorkshop.h>
#include <exw\EntryPoint.h>

class ExToolbox : public exw::Application
{
public:
    ExToolbox()
        :Application("ExToolbox")
    {

    }

    ~ExToolbox() {}
};

exw::Application* exw::create_application()
{
    return new ExToolbox();
}
