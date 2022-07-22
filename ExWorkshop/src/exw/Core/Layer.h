/*  Layer.h
*   Version: 1.0 (2022.07.21)
*
*   Contributor
*       Arime-chan
*/
#pragma once

#include "exw\Events\Event.h"

namespace exw
{
    class Layer
    {
    public:
        Layer(const std::string& _name = "Layer");
        virtual ~Layer() = default;

        virtual void attach() {}
        virtual void detach() {}
        virtual void update(float _deltaTime) {}

        virtual void on_event(events::Event& _event) {}

        const std::string get_name() const { return m_Name; }

    protected:
        std::string m_Name;
    };

}
