// ;
#include "expch.h"
#include "Application.h"

namespace exw
{
    Application* Application::s_Instance = nullptr;

    Application::Application(const std::string& _name)
    {
        EXW_ASSERT(s_Instance == nullptr, "Application is currently running.");
        
        s_Instance = this;

        m_Is_running = true;
    }

    Application::~Application()
    {}

    void Application::close()
    {
        m_Is_running = false;
    }
    
    void Application::run()
    {
        while (m_Is_running)
        {
            // update;
            if (!m_Is_minimized)
            {

            }

            // render;
            {
                if (!m_Is_minimized)
                {

                }
            }
        }
    }
}
