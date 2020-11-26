// ;
#include "expch.h"
#include "exw\graphics\Buffers.h"

#include "exw\graphics\RenderAPI.h"

#include "platform\OpenGL\OpenGLBuffers.h"

namespace exw
{
    namespace graphics
    {
        refs::ref<VertexBuffer> VertexBuffer::create(uint32_t _size)
        {
            switch (RenderAPI::get())
            {
                case RenderAPI::API::None:      EXW_ASSERT(false, "RenderAPI::None is not supported."); return nullptr;
                case RenderAPI::API::OpenGL:    return refs::create_ref<OpenGLVertexBuffer>(_size);
                case RenderAPI::API::DirectX:   EXW_ASSERT(false, "RenderAPI::DirectX is not supported."); return nullptr;
                case RenderAPI::API::Vulkan:    EXW_ASSERT(false, "RenderAPI::Vulkan is not supported."); return nullptr;
            }

            EXW_ASSERT(false, "Unknown RenderAPI is not supported.");
            return nullptr;
        }

        refs::ref<VertexBuffer> VertexBuffer::create(float* _vertices, uint32_t _size)
        {
            switch (RenderAPI::get())
            {
                case RenderAPI::API::None:      EXW_ASSERT(false, "RenderAPI::None is not supported."); return nullptr;
                case RenderAPI::API::OpenGL:    return refs::create_ref<OpenGLVertexBuffer>(_vertices, _size);
                case RenderAPI::API::DirectX:   EXW_ASSERT(false, "RenderAPI::DirectX is not supported."); return nullptr;
                case RenderAPI::API::Vulkan:    EXW_ASSERT(false, "RenderAPI::Vulkan is not supported."); return nullptr;
            }

            EXW_ASSERT(false, "Unknown RenderAPI is not supported.");
            return nullptr;
        }

        refs::ref<IndexBuffer> IndexBuffer::create(uint32_t* _indices, uint32_t _count)
        {
            switch (RenderAPI::get())
            {
                case RenderAPI::API::None:      EXW_ASSERT(false, "RenderAPI::None is not supported."); return nullptr;
                case RenderAPI::API::OpenGL:    return refs::create_ref<OpenGLIndexBuffer>(_indices, _count);
                case RenderAPI::API::DirectX:   EXW_ASSERT(false, "RenderAPI::DirectX is not supported."); return nullptr;
                case RenderAPI::API::Vulkan:    EXW_ASSERT(false, "RenderAPI::Vulkan is not supported."); return nullptr;
            }

            EXW_ASSERT(false, "Unknown RenderAPI is not supported.");
            return nullptr;
        }
    }
}
