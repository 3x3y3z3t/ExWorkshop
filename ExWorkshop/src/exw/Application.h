// ;
#pragma once

#include "exw\Common.h"

#include "Window.h"
#include "exw\events\Events.h"
#include "exw\layers\Layer.h"
#include "exw\layers\LayerStack.h"
#include "exw\gui\GuiLayer.h"

int main(int _argc, char* _argv[]);

namespace exw
{
    class Application
    {
    public:
        Application(const std::string& _name = "", uint32_t _width = 1280U, uint32_t _height = 720U);
        virtual ~Application();

    public:
        void close();
        void on_event(event::Event& _event);

        void push_layer(Layer* _layer);
        void push_overlay(Layer* _overlay);

        Window& get_window() { return *m_Window; }
        gui::GuiLayer* get_gui_layer() { return m_Gui_layer; }

        static Application& get() { return *s_Instance; }
    private:
        void run();

    private:
        bool m_Is_running = false;
        bool m_Is_minimized = false;
        float m_Last_frametime = 0.0f;
        gui::GuiLayer* m_Gui_layer = nullptr;

        refs::scope<Window> m_Window;

        LayerStack m_Layer_stack;

        static Application* s_Instance;
        friend int ::main(int _argc, char* _argv[]);
    };

    Application* create_application();
}
