/*  OpenGLContext.h
*   Version: 1.0 (2022.07.22)
*
*   Contributor
*       Arime-chan
*/
#pragma once

#include "exw\graphics\GraphicsContext.h"

class GLFWwindow;

namespace exw
{
    namespace graphics
    {
        class OpenGLContext : public GraphicsContext
        {
        public:
            OpenGLContext(GLFWwindow* _window);

            virtual void init() override;
            virtual void swap_buffers() override;

        private:
            GLFWwindow* m_Window = nullptr;
        };
    }
}
