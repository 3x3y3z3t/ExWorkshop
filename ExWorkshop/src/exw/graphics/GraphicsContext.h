/*  GraphicsContext.h
*   Version: 1.0 (2022.07.22)
*
*   Contributor
*       Arime-chan
*/
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

            static refs::Scoped<GraphicsContext> create(void* _window);

            virtual void init() = 0;
            virtual void swap_buffers() = 0;
        };
    }
}
