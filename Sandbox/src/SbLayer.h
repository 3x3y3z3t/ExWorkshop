// ;
#pragma once

#include <ExWorkshop.h>

namespace sb
{
    class SbLayer : public exw::Layer
    {
    public:
        SbLayer();

        virtual void attach() override;
        virtual void detach() override;
        virtual void update(exw::Timestep _ts) override;
        virtual void render_gui() override;

        virtual void on_event(exw::event::Event& _event) override;

    private:
        exw::refs::ref<exw::Scene> m_Active_scene;
        exw::Entity m_Square;
        exw::Entity m_Camera;
    };
}
