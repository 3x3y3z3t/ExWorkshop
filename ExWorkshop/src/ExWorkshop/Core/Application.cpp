/*  Application.cpp
*   Version: 1.1 (2022.07.21)
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
            EXW_CORE_LOG_CRITICAL("An instance of application is already running.");
            return; // TODO: assert;
        }

        if (!m_Working_dir.empty())
            std::filesystem::current_path(m_Working_dir);

        EXW_CORE_LOG_TRACE("Creating Application..");
        EXW_CORE_LOG_TRACE("  App name         : {0}", m_App_name);
        EXW_CORE_LOG_TRACE("  Working directory: {0}", std::filesystem::current_path());
        EXW_CORE_LOG_TRACE("  Command Line Args: {0}", m_Args.Count);
        for (int i = 0; i < m_Args.Count; ++i)
        {
            EXW_CORE_LOG_TRACE("    {0}", m_Args[i]);
        }

        m_Running = true;
        m_Minimized = false;

        s_Instance = this;

        EXW_CORE_LOG_TRACE("  >> Done.");
    }

    Application::~Application()
    {
        EXW_CORE_LOG_TRACE("Closing Application..");

        EXW_CORE_LOG_TRACE("  >> Done.");
    }

    void Application::close()
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
        events::EventDispatcher dispatcher(_event);

        for (auto iterator = m_Layers.rbegin(); iterator != m_Layers.rend(); ++iterator)
        {
            if (_event.Handled)
                break;

            (*iterator)->on_event(_event);
        }


    }

    void Application::run()
    {
        EXW_CORE_LOG_DEBUG("Application::run()");
        while (m_Running)
        {
            if (!m_Minimized)
            {
                for (events::Layer* layer : m_Layers)
                {
                    layer->update(16.667f); // fixed 60fps;
                }
            }


            ++m_Last_frame_time; // +1 ticks

            if (m_Last_frame_time = 100'000)
                break;
        }
        EXW_CORE_LOG_DEBUG("  End run.");
    }

}


