// ;
#include "expch.h"
#include "exw\layers\Layer.h"

namespace exw
{
    Layer::Layer(const std::string& _name)
        : m_Name(_name)
    {}

    void Layer::attach()
    {}

    void Layer::detach()
    {}

    void Layer::update(Timestep _ts)
    {}

    void Layer::render_gui()
    {}

    void Layer::on_event(event::Event& _event)
    {}
}
