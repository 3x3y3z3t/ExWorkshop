// ;
#pragma once
#include "expch.h"

#include "exw\Common.h"

int main(int _argc, char* _argv[]);

namespace exw
{
    class Application
    {
    public:
        Application(const std::string& _name = "");
        virtual ~Application();

    public:
        void close();

        static Application& get() { return *s_Instance; }
    private:
        void run();

    private:
        bool m_Is_running = false;
        bool m_Is_minimized = false;
        float m_Last_frametime = 0.0f;

        static Application* s_Instance;
        friend int ::main(int _argc, char* _argv[]);
    };

    Application* create_application();
}
