/*  SandboxApp.cpp
*   Version: 1.0 (2022.07.21)
*
*   Contributor
*       Arime-chan
*/

#include <ExWorkshop.h>

class SandboxLayer : public exw::Layer
{
public:
    SandboxLayer()
        : exw::Layer("SandboxLayer")
    {}

    virtual void attach()
    {}

    virtual void detach()
    {}

    virtual void update(float _deltaTime)
    {
        using namespace exw;

        if (Input::is_key_pressed(Keys::A))
            EXW_LOG_DEBUG("Å©");
        else if (Input::is_key_pressed(Keys::D))
            EXW_LOG_DEBUG("Å®");

        if (Input::is_key_pressed(Keys::W))
            EXW_LOG_DEBUG("Å™");
        else if (Input::is_key_pressed(Keys::S))
            EXW_LOG_DEBUG("Å´");

        if (Input::is_mouse_btn_pressed(MouseBtn::Button0))
        {
            auto cursorPos = Input::get_cursor_pos();
            EXW_LOG_DEBUG("Pressed ({0}, {1})", cursorPos.first, cursorPos.second);
        }
    }

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
