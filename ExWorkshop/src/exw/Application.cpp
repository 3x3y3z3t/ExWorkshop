// ;
#include "expch.h"
#include "Application.h"

#include "exw\utils\Timestep.h"
#include "exw\utils\Random.h"

#include <GLFW\glfw3.h>

namespace exw
{
    Application* Application::s_Instance = nullptr;

    Application::Application(const std::string& _name, uint32_t _width, uint32_t _height)
    {
        EXW_ASSERT(s_Instance == nullptr, "Application is currently running.");
        s_Instance = this;
        m_Window = Window::create({ _name, _width, _height });
        m_Window->set_event_callback(EXW_BIND_EVENT_FUNCTION(Application::on_event));


        utils::RNG32::init();

        m_Is_running = true;
    }

    Application::~Application()
    {}

    void Application::close()
    {
        m_Is_running = false;
    }

    void Application::on_event(event::Event& _event)
    {
        event::EventDispatcher dispatcher(_event);

        dispatcher.dispatch<event::WindowCloseEvent>([&] (event::WindowCloseEvent& _evt)
        {
            m_Is_running = false;
            return true;
        });

        dispatcher.dispatch<event::WindowResizeEvent>([&] (event::WindowResizeEvent& _evt)
        {
            if (_evt.get_width() == 0 || _evt.get_height() == 0)
            {
                m_Is_minimized = true;
                return false;
            }

            m_Is_minimized = false;

            return false;
        });

        for (auto it = m_Layer_stack.rbegin(); it != m_Layer_stack.rend(); ++it)
        {
            if (_event.Handled)
                break;
            (*it)->on_event(_event);
        }
    }

    void Application::push_layer(Layer* _layer)
    {}

    void Application::push_overlay(Layer* _overlay)
    {}

    void Application::run()
    {
        while (m_Is_running)
        {
            float time = (float)(glfwGetTime() * 1000.0);
            Timestep timestep = time - m_Last_frametime;
            m_Last_frametime = time;

            if (!m_Is_minimized)
            {
                for (Layer* layer : m_Layer_stack)
                    layer->update(timestep);
            }

            m_Window->update();
        }   
    }
}
