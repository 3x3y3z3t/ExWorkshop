// ;
#pragma once

#include "exw\layers\Layer.h"

namespace exw
{
    namespace gui
    {
        class GuiLayer : public Layer
        {
        public:
            GuiLayer(const std::string& _name);
            virtual ~GuiLayer() = default;

        public:
            virtual void begin() = 0;
            virtual void end() = 0;

            bool is_events_blocked() const { return m_Block_events; }

            void block_events(bool _enabled) { m_Block_events = _enabled; }

        protected:
            bool m_Block_events = false;
        };
    }
}
