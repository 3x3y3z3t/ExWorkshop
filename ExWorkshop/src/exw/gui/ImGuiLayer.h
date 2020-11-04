// ;
#pragma once

#include "GuiLayer.h"

#include "exw\events\Events.h"

namespace exw
{
    namespace gui
    {
        class ImGuiLayer : public GuiLayer
        {
        public:
            ImGuiLayer();
            ~ImGuiLayer() = default;

        public:
            virtual void begin() override;
            virtual void end() override;

            void set_dark_theme_colors();

            virtual void attach() override;
            virtual void detach() override;
            //virtual void update(Timestep _ts) override;
            virtual void render_gui() override;

            virtual void on_event(event::Event& _event) override;

        private:
            float m_Time = 0.0f;
        };
    }
}
