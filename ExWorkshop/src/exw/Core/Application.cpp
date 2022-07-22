/*  Application.cpp
*   Version: 1.4 (2022.07.22)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "Application.h"

#include <glad\gl.h>

namespace exw
{
    Application* Application::s_Instance = nullptr;

    uint32_t Vertex_array = 0U;
    uint32_t Vertex_buffer = 0U;
    uint32_t Index_buffer = 0U;

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

        EXW_LOG_CORE_INFO("App info:");
        EXW_LOG_CORE_INFO("  App name         : {0}", _name);
        EXW_LOG_CORE_INFO("  Working directory: {0}", std::filesystem::current_path());
        EXW_LOG_CORE_INFO("  Command Line Args: {0}", _args.Count);
        for (int i = 0; i < m_Args.Count; ++i)
        {
            EXW_LOG_CORE_INFO("    {0}", m_Args[i]);
        }

        EXW_LOG_CORE_TRACE("Creating window..");
        EXW_LOG_CORE_INDENT_IN();
        {
            m_Window = Window::create(WindowProperties(_name));


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

        glGenVertexArrays(1, &Vertex_array);
        glBindVertexArray(Vertex_array);

        glGenBuffers(1, &Vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, Vertex_buffer);

        float vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        glGenBuffers(1, &Index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Index_buffer);

        uint32_t indices[6] = { 0, 1, 2 };

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);




        EXW_LOG_CORE_TRACE("<< Done.");
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
            if (!m_Minimized)
            {
                for (Layer* layer : m_Layers)
                {
                    layer->update(16.667f); // fixed 60fps;
                }
            }

            glClear(GL_COLOR_BUFFER_BIT);
            glBindVertexArray(Vertex_array);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);




            m_Window->update();
        }
        EXW_LOG_CORE_DEBUG("  End run.");
    }

}


