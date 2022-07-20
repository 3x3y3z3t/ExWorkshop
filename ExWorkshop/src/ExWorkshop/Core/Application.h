/*  Application.h
*   Version: 1.0 (2022.07.20)
*
*   Contributor
*       Arime-chan
*/

#pragma once

#include "exwpch.h"

#include "ExWorkshop\Utils\Logger.h"

int main(int _argc, char* _argv[], char* _envp[]);

namespace exw
{
    struct AppCommandLineArgs
    {
        int Count = 0;
        char** Args = nullptr;

        const char* operator[](int _index) const
        {
            if (_index >= Count)
            {
                EXW_CORE_LOG_CRITICAL("Index out of range.");
                return ""; // TODO: assert;
            }
            return Args[_index];
        }
    };

    class Application
    {
    public:
        Application(std::string _name, std::string _workingDir, AppCommandLineArgs _args);
        virtual ~Application();

        static Application& get() { return *s_Instance; }

        void close();

    private:
        void run();

    private:
        static Application* s_Instance;

        bool m_Running = false;

        float m_Last_frame_time = 0.0f;

        std::string m_App_name = "";
        std::string m_Working_dir = "";
        AppCommandLineArgs m_Args = {};

        friend int ::main(int _argc, char* _argv[], char* _envp[]);
    };

    Application* create_application(AppCommandLineArgs _args);
}
