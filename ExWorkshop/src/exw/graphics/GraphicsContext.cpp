/*  GraphicsContext.cpp
*   Version: 1.0 (2022.07.22)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "GraphicsContext.h"

#include "Renderer.h"
#include "exw\Common.h"
#include "exw\utils\Logger.h"

#include "Platform\OpenGL\OpenGLContext.h"

#include <GLFW\glfw3.h>

namespace exw
{
    namespace graphics
    {
        refs::Scoped<GraphicsContext> GraphicsContext::create(void* _window)
        {
            return refs::create_scoped<OpenGLContext>(static_cast<GLFWwindow*>(_window));

            //RendererAPI activeApi = Renderer::get_active_api();
            //switch (activeApi)
            //{
            //    case RendererAPI::OpenGL:   return refs::create_scoped<OpenGLContext>(static_cast<GLFWwindow*>(_window));
            //}

            //EXW_LOG_CORE_CRITICAL("RendererAPI {0} is not supported.", activeApi);
            return nullptr;
        }

    }
}
