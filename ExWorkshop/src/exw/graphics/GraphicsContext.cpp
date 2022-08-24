/*  GraphicsContext.cpp
*   Version: 1.1 (2022.08.24)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "GraphicsContext.h"

#include "Renderer.h"
#include "exw\Common.h"
#include "exw\utils\Logger.h"

#include "platform\OpenGL\OpenGLContext.h"

#include <GLFW\glfw3.h>

namespace exw
{
    namespace graphics
    {
        refs::Scoped<GraphicsContext> GraphicsContext::create(void* _window)
        {
            RendererAPI::API activeApi = Renderer::get_active_api();
            switch (activeApi)
            {
                case RendererAPI::API::OpenGL:   return refs::create_scoped<OpenGLContext>(static_cast<GLFWwindow*>(_window));
            }

            EXW_LOG_CORE_CRITICAL("RendererAPI {0} is not supported.", (uint8_t)activeApi);
            return nullptr;
        }

    }
}
