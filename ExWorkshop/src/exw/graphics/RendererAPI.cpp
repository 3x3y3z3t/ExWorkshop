/*  RendererAPI.cpp
*   Version: 1.0 (2022.08.24)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "RendererAPI.h"

#include "exw\utils\Logger.h"
#include "Platform\OpenGL\OpenGLRendererAPI.h"

namespace exw
{
    namespace graphics
    {
        RendererAPI::API RendererAPI::s_Active_api = RendererAPI::API::None;

        refs::Scoped<RendererAPI> RendererAPI::create()
        {
            RendererAPI::API activeApi = Renderer::get_active_api();
            switch (activeApi)
            {
                case RendererAPI::API::OpenGL:   return refs::create_scoped<OpenGLRendererAPI>();
            }

            EXW_LOG_CORE_CRITICAL("RendererAPI {0} is not supported.", (uint8_t)activeApi);
            return nullptr;
        }

    }
}
