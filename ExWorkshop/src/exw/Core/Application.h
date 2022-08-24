/*  Application.h
*   Version: 1.3 (2022.08.24)
*
*   Contributor
*       Arime-chan
*/
#pragma once
#include "exwpch.h"

#include "Window.h"
#include "exw\core\Layer.h"
#include "exw\core\LayerStack.h"
#include "exw\events\Event.h"
#include "exw\events\WindowEvent.h"
#include "exw\graphics\RendererAPI.h"
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
            if (_index >= Count)
            {
                EXW_LOG_CORE_CRITICAL("Index out of range.");
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

        void shutdown();

        void switch_renderer_api(graphics::RendererAPI::API _api);

        void push_layer(Layer* _layer);
        void push_overlay(Layer* _overlay);

        void on_event(events::Event& _event);

        Window& get_window() { return *m_Window; }

    private:
        void run();

    private:
        static Application* s_Instance;

        bool m_Running = false;
        bool m_Minimized = false;
        float m_Last_frame_time = 0.0f;

        std::string m_App_name;
        std::string m_Working_dir;
        AppCommandLineArgs m_Args;

        LayerStack m_Layers;

        refs::Scoped<Window> m_Window;

        friend int ::main(int _argc, char* _argv[], char* _envp[]);
    };

    Application* create_application(AppCommandLineArgs _args);

}
