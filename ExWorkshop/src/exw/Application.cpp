// ;
#include "expch.h"
#include "Application.h"

#include "exw\graphics\Renderer.h"
#include "exw\gui\ImGuiLayer.h"
#include "exw\utils\Timestep.h"
#include "exw\utils\Random.h"

#include <GLFW\glfw3.h>

namespace exw
{
    Application* Application::s_Instance = nullptr;

    Application::Application(const std::string& _name, uint32_t _width, uint32_t _height)
    {
        EXW_PROFILE_FUNCTION();
        EXW_ASSERT(s_Instance == nullptr, "Application is currently running.");
        s_Instance = this;
        m_Window = Window::create({ _name, _width, _height });
        m_Window->set_event_callback(EXW_BIND_EVENT_FUNCTION(Application::on_event));

        graphics::Renderer::init();

        utils::RNG32::init();

        m_Gui_layer = new gui::ImGuiLayer();
        push_overlay(m_Gui_layer);

        m_Is_running = true;
    }

    Application::~Application()
    {
        EXW_PROFILE_FUNCTION();
        graphics::Renderer::shutdown();
    }

    void Application::close()
    {
        m_Is_running = false;
    }

    void Application::on_event(event::Event& _event)
    {
        EXW_PROFILE_FUNCTION();
        event::EventDispatcher dispatcher(_event);

        dispatcher.dispatch<event::WindowCloseEvent>([&] (event::WindowCloseEvent& _evt)
        {
            m_Is_running = false;
            return true;
        });

        dispatcher.dispatch<event::WindowResizeEvent>([&] (event::WindowResizeEvent& _evt)
        {
            EXW_PROFILE_FUNCTION();
            if (_evt.get_width() == 0 || _evt.get_height() == 0)
            {
                m_Is_minimized = true;
                return false;
            }

            m_Is_minimized = false;
            graphics::Renderer::on_window_resize(_evt.get_width(), _evt.get_height());

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
    {
        EXW_PROFILE_FUNCTION();
        m_Layer_stack.push_layer(_layer);
        _layer->attach();
    }

    void Application::push_overlay(Layer* _overlay)
    {
        EXW_PROFILE_FUNCTION();
        m_Layer_stack.push_overlay(_overlay);
        _overlay->attach();
    }

    void Application::run()
    {
        EXW_PROFILE_FUNCTION();
        while (m_Is_running)
        {
            float time = (float)(glfwGetTime() * 1000.0);
            Timestep timestep = time - m_Last_frametime;
            m_Last_frametime = time;
            //EXW_LOG_DEBUG("frametime = {0}", timestep);

            if (!m_Is_minimized)
            {
                EXW_PROFILE_SCOPE("LayerStack update");
                for (Layer* layer : m_Layer_stack)
                    layer->update(timestep);

                m_Gui_layer->begin();
                {
                    EXW_PROFILE_SCOPE("LayerStack render gui (ImGui)");

                    for (Layer* layer : m_Layer_stack)
                        layer->render_gui();
                }
                m_Gui_layer->end();
            }

            {
                EXW_PROFILE_SCOPE("Window update");
                m_Window->update();
            }
        }
    }
}
