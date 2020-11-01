// ;
#pragma once

#include "exw\Common.h"

namespace exw
{
    namespace graphics
    {
        class GraphicsContext
        {
        public:
            virtual ~GraphicsContext() = default;

        public:
            virtual void init() = 0;
            virtual void swap_buffers() = 0;

            static refs::scope<GraphicsContext> create(void* _window);
        };
    }
}
