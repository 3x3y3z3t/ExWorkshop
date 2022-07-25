/*  Application.cpp
*   Version: 1.5 (2022.07.25)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "Application.h"

#include "exw\utils\DateTime.h"

namespace exw
{
    Application* Application::s_Instance = nullptr;

    Application::Application(const AppSpecification& _specification)
        : m_Specification(_specification)
    {
        EXW_ASSERT_CORE(s_Instance == nullptr, "An instance of application is already running.");

        if (!_specification.WorkingDir.empty())
            std::filesystem::current_path(_specification.WorkingDir);

        EXW_LOG_CORE_INFO("App info:");
        EXW_LOG_CORE_INFO("  App name         : {0}", _specification.Name);
        EXW_LOG_CORE_INFO("  Working directory: {0}", std::filesystem::current_path());
        EXW_LOG_CORE_INFO("  Command Line Args: {0}", _specification.CommandLineArgs.Count);
        for (int i = 0; i < _specification.CommandLineArgs.Count; ++i)
        {
            EXW_LOG_CORE_INFO("    {0}", _specification.CommandLineArgs[i]);
        }

        EXW_LOG_CORE_TRACE("Creating window..");
        EXW_LOG_CORE_INDENT_IN();
        {
            m_Window = Window::create(WindowProperties(_specification.Name));
            m_Window->set_event_callback([this] (auto&... _args) -> decltype(auto)
            {
                return this->on_event(std::forward<decltype(_args)>(_args)...);
            });
        }
        EXW_LOG_CORE_INDENT_OUT();
        EXW_LOG_CORE_TRACE("Window created.");



        m_Running = true;
        m_Minimized = false;

        s_Instance = this;

        EXW_LOG_CORE_TRACE("<< Done.");
    }

    Application::~Application()
    {

        EXW_LOG_CORE_TRACE("<< Done.");
    }

    void Application::shutdown()
    {
        m_Running = false;
    }

    void Application::push_layer(Layer* _layer)
    {
        m_Layers.push_layer(_layer);
        _layer->attach();
    }

    void Application::push_overlay(Layer* _overlay)
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
            float time = utils::Time::get_time_as_float();

            float dt = time - m_Last_update_time;
            if (dt >= 1.0f / (float)m_Max_ups)
            {
                //EXW_LOG_CORE_DEBUG("Window update delay = {0}", dt - (1.0f / (float)m_Max_ups));

                m_Last_update_time = time;

                for (Layer* layer : m_Layers)
                {
                    layer->update(dt); // fixed 60ups;
                }
            }

            if (!m_Minimized)
            {
                dt = time - m_Last_render_time;
                if (dt >= 1.0f / (float)m_Max_fps)
                {
                    m_Last_render_time = time;

                    for (Layer* layer : m_Layers)
                    {
                        //layer->render(dt); // fixed 60fps;
                    }
                }
            }


            m_Window->update();
        }
        EXW_LOG_CORE_DEBUG("  End run.");
    }

}


