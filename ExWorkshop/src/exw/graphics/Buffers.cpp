/*  Buffers.cpp
*   Version: 1.0 (2022.07.23)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "Buffers.h"

#include "Renderer.h"
#include "exw\utils\Logger.h"
#include "platform\OpenGL\OpenGLBuffers.h"

namespace exw
{
    namespace graphics
    {
        refs::Ref<VertexBuffer> VertexBuffer::create(uint32_t _size)
        {
            RendererAPI::API activeApi = Renderer::get_active_api();
            switch (activeApi)
            {
                case RendererAPI::API::OpenGL:   return refs::create_ref<OpenGLVertexBuffer>(_size);
            }

            EXW_LOG_CORE_CRITICAL("RendererAPI {0} is not supported.", (uint8_t)activeApi);
            return nullptr;
        }

        refs::Ref<VertexBuffer> VertexBuffer::create(float* _vertices, uint32_t _size)
        {
            RendererAPI::API activeApi = Renderer::get_active_api();
            switch (activeApi)
            {
                case RendererAPI::API::OpenGL:   return refs::create_ref<OpenGLVertexBuffer>(_vertices, _size);
            }

            EXW_LOG_CORE_CRITICAL("RendererAPI {0} is not supported.", (uint8_t)activeApi);
            return nullptr;
        }

        refs::Ref<IndexBuffer> IndexBuffer::create(uint32_t* _indices, uint32_t _count)
        {
            RendererAPI::API activeApi = Renderer::get_active_api();
            switch (activeApi)
            {
                case RendererAPI::API::OpenGL:   return refs::create_ref<OpenGLIndexBuffer>(_indices, _count);
            }

            EXW_LOG_CORE_CRITICAL("RendererAPI {0} is not supported.", (uint8_t)activeApi);
            return nullptr;
        }

    }
}
