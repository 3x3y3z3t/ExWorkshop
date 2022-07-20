/*  Application.h
*   Version: 1.0 (2022.07.20)
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

        s_Instance = this;
    }

    Application::~Application()
    {

    }

    void Application::close()
    {
        EXW_CORE_LOG_TRACE("Application is closing..");
        m_Running = false;
    }

    void Application::run()
    {
        EXW_CORE_LOG_DEBUG("Application::run()");
        while (m_Running)
        {
            ++m_Last_frame_time; // +1 ticks

            if (m_Last_frame_time = 100'000)
                break;
        }
        EXW_CORE_LOG_DEBUG("  End run.");
    }
}


