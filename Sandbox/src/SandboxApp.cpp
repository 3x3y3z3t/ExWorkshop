/*  SandboxApp.cpp
*   Version: 1.0 (2022.07.21)
*
*   Contributor
*       Arime-chan
*/

#include <ExWorkshop.h>

class SandboxLayer : public exw::events::Layer
{
public:
    SandboxLayer()
        : exw::events::Layer("SandboxLayer")
    {}

    virtual void attach()
    {}

    virtual void detach()
    {}

    virtual void update(float _deltaTime)
    {}

    virtual void on_event(exw::events::Event& _event)
    {}
};

class Sandbox : public exw::Application
{
public:
    Sandbox(std::string _name, std::string _workingDir, exw::AppCommandLineArgs _args)
        : exw::Application(_name, _workingDir, _args)
    {
        push_layer(new SandboxLayer());
    }

    ~Sandbox()
    {}
};

exw::Application* exw::create_application(exw::AppCommandLineArgs _args)
{
    return new Sandbox("Sandbox", ".", _args);
}
