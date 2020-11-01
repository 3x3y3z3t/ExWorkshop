// ;
#pragma once

#include "exw\graphics\GraphicsContext.h"

struct GLFWwindow;

namespace exw
{
    namespace graphics
    {
        class OpenGLGraphicsContext : public GraphicsContext
        {
        public:
            OpenGLGraphicsContext(GLFWwindow* _window);

        public:
            virtual void init() override;
            virtual void swap_buffers() override;

        private:
            GLFWwindow* m_Window;
        };
    }
}
