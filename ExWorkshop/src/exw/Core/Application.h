/*  Application.h
*   Version: 1.4 (2022.07.25)
*
*   Contributor
*       Arime-chan
*/
#pragma once
#include "exwpch.h"

#include "Window.h"

#include "exw\Common.h"
#include "exw\core\Layer.h"
#include "exw\core\LayerStack.h"
#include "exw\events\Event.h"
#include "exw\events\WindowEvent.h"
#include "exw\utils\Logger.h"

int main(int _argc, char* _argv[], char* _envp[]);

namespace exw
{
    struct AppCommandLineArgs
    {
        int Count = 0;
        char** Args = nullptr;

        const char* operator[](int _index) const
        {
            EXW_ASSERT_CORE(_index < Count, "Index out of range");
            return Args[_index];
        }
    };

    struct AppSpecification
    {
        std::string Name = "ExWorkshop";
        std::string WorkingDir;
        AppCommandLineArgs CommandLineArgs;
    };

    class Application
    {
    public:
        Application(const AppSpecification& _specification);
        virtual ~Application();

        static Application& get() { return *s_Instance; }

        void shutdown();

        void push_layer(Layer* _layer);
        void push_overlay(Layer* _overlay);

        void on_event(events::Event& _event);

        Window& get_window() { return *m_Window; }
        const AppSpecification& get_specification() const { return m_Specification; }

        void set_max_fps(uint32_t _maxFps) { m_Max_fps = _maxFps; }
        void set_max_ups(uint32_t _maxUps) { m_Max_ups = _maxUps; }

    private:
        void run();

    private:
        static Application* s_Instance;

        bool m_Running = false;
        bool m_Minimized = false;
        float m_Last_render_time = 0.0f;
        float m_Last_update_time = 0.0f;

        uint32_t m_Max_fps = 60U;
        uint32_t m_Max_ups = 60U;

        AppSpecification m_Specification;

        LayerStack m_Layers;

        refs::Scoped<Window> m_Window;

        friend int ::main(int _argc, char* _argv[], char* _envp[]);
    };

    Application* create_application(AppCommandLineArgs _args);

}
