// ;
#pragma once

#include "exw\Common.h"
#include "exw\events\Event.h"
#include "exw\utils\Timestep.h"

namespace exw
{
    class Layer
    {
    public:
        Layer(const std::string& _name = "Layer");
        virtual ~Layer() = default;

    public:
        virtual void attach();
        virtual void detach();
        virtual void update(Timestep _ts);
        virtual void render_gui();

        virtual void on_event(event::Event& _event);

        const std::string& get_name() const { return m_Name; }

    protected:
        std::string m_Name;
    };
}
