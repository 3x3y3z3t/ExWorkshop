/*  Application.cpp
*   Version: 1.3 (2022.07.22)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "Application.h"

namespace exw
{
    Application* Application::s_Instance = nullptr;

    Application::Application(std::string _name, std::string _workingDir, AppCommandLineArgs _args)
        : m_App_name(_name), m_Working_dir(_workingDir), m_Args(_args)
    {
        if (s_Instance != nullptr)
        {
            utils::Logger::core_critical("An instance of application is already running.");
            return; // TODO: assert;
        }

        if (!m_Working_dir.empty())
            std::filesystem::current_path(m_Working_dir);

        EXW_LOG_CORE_TRACE("Creating Application..");
        EXW_LOG_CORE_TRACE("  App name         : {0}", _name);
        EXW_LOG_CORE_TRACE("  Working directory: {0}", std::filesystem::current_path());
        EXW_LOG_CORE_TRACE("  Command Line Args: {0}", _args.Count);
        for (int i = 0; i < m_Args.Count; ++i)
        {
            EXW_LOG_CORE_TRACE("    {0}", m_Args[i]);
        }

        EXW_LOG_CORE_INDENT_IN();
        m_Window = Window::create(WindowProperties(_name));
        m_Window->set_event_callback([this] (auto&... _args) -> decltype(auto)
        {
            return this->on_event(std::forward<decltype(_args)>(_args)...);
        });
        EXW_LOG_CORE_INDENT_OUT();



        m_Running = true;
        m_Minimized = false;

        s_Instance = this;

        EXW_LOG_CORE_TRACE("  << Done.");
    }

    Application::~Application()
    {
        EXW_LOG_CORE_TRACE("Closing Application..");

        EXW_LOG_CORE_TRACE("  << Done.");
    }

    void Application::shutdown()
    {
        m_Running = false;
    }

    void Application::push_layer(events::Layer* _layer)
    {
        m_Layers.push_layer(_layer);
        _layer->attach();
    }

    void Application::push_overlay(events::Layer* _overlay)
    {
        m_Layers.push_overlay(_overlay);
        _overlay->attach();
    }

    void Application::on_event(events::Event& _event)
    {
        using namespace events;
        EventDispatcher dispatcher(_event);
        dispatcher.dispatch<WindowResizedEvent>([&] (WindowResizedEvent& _evt)
        {
            if (_evt.get_width() == 0U || _evt.get_height() == 0U)
            {
                m_Minimized = true;
                return false;
            }

            m_Minimized = false;

            return false;
        });
        dispatcher.dispatch<WindowClosedEvent>([&] (WindowClosedEvent& _evt)
        {
            m_Running = false;
            return true;
        });


        for (auto iterator = m_Layers.rbegin(); iterator != m_Layers.rend(); ++iterator)
        {
            if (_event.Handled)
                break;

            (*iterator)->on_event(_event);
        }


    }

    void Application::run()
    {
        EXW_LOG_CORE_DEBUG("Application::run()");
        while (m_Running)
        {
            if (!m_Minimized)
            {
                for (events::Layer* layer : m_Layers)
                {
                    layer->update(16.667f); // fixed 60fps;
                }
            }

            m_Window->update();
        }
        EXW_LOG_CORE_DEBUG("  End run.");
    }

}


