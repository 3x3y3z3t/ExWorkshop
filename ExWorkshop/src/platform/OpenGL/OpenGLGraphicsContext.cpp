// ;
#include "expch.h"
#include "OpenGLGraphicsContext.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

namespace exw
{
    namespace graphics
    {
        OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* _window)
            : m_Window(_window)
        {
            EXW_ASSERT(_window != nullptr, "Window is null?");
        }

        void OpenGLGraphicsContext::init()
        {
            EXW_PROFILE_FUNCTION();
            glfwMakeContextCurrent(m_Window);
            int stat = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            EXW_ASSERT(stat, "Glad initialization failure.");

            EXW_LOG_INFO("OpenGL version {0} ({1})", glGetString(GL_VERSION), glGetString(GL_RENDERER));

            int versionMajor, versionMinor;
            glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
            glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
            EXW_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "ExWorkshop requires OpenGL 4.5 or higher.");
        }

        void OpenGLGraphicsContext::swap_buffers()
        {
            EXW_PROFILE_FUNCTION();
            glfwSwapBuffers(m_Window);
        }
    }
}
