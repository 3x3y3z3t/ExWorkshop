/*  VertexArray.cpp
*   Version: 1.0 (2022.07.24)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "exw\utils\Logger.h"
#include "Platform\OpenGL\OpenGLVertexArray.h"

namespace exw
{
    namespace graphics
    {
        refs::Ref<VertexArray> VertexArray::create()
        {
            RendererAPI::API activeApi = Renderer::get_active_api();
            switch (activeApi)
            {
                case RendererAPI::API::OpenGL:   return refs::create_ref<OpenGLVertexArray>();
            }

            EXW_LOG_CORE_CRITICAL("RendererAPI {0} is not supported.", (uint8_t)activeApi);
            return nullptr;
        }

    }
}
