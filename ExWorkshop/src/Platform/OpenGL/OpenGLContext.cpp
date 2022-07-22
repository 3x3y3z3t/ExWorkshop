/*  OpenGLContext.cpp
*   Version: 1.0 (2022.07.22)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "OpenGLContext.h"

#include "exw\Common.h"
#include "exw\utils\Logger.h"

#include <glad\gl.h>
#include <GLFW\glfw3.h>

namespace exw
{
    namespace graphics
    {
        OpenGLContext::OpenGLContext(GLFWwindow* _window)
            : m_Window(_window)
        {
            if (_window == nullptr)
                EXW_LOG_CORE_CRITICAL("Window is null.");
        }

        void OpenGLContext::init()
        {
            glfwMakeContextCurrent(m_Window);

            int status = gladLoadGL((GLADloadfunc)glfwGetProcAddress);
            if (status == 0)
            {
                EXW_LOG_CORE_CRITICAL("Failed to initialize Glad.");
                return;
            }

            EXW_LOG_CORE_TRACE("OpenGL info:");
            EXW_LOG_CORE_INFO("  Vendor  : {0}", glGetString(GL_VENDOR));
            EXW_LOG_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
            EXW_LOG_CORE_INFO("  Version : {0}", glGetString(GL_VERSION));

            EXW_LOG_CORE_TRACE("<< Done.");
        }

        void OpenGLContext::swap_buffers()
        {
            glfwSwapBuffers(m_Window);
        }
    }
}
