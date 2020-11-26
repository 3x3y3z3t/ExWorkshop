// ;
#include "expch.h"
#include "exw\graphics\VertexArray.h"

#include "exw\graphics\RenderAPI.h"

#include "platform\OpenGL\OpenGLVertexArray.h"

namespace exw
{
    namespace graphics
    {
        refs::ref<VertexArray> VertexArray::create()
        {
            switch (RenderAPI::get())
            {
                case RenderAPI::API::None:      EXW_ASSERT(false, "RenderAPI::None is not supported."); return nullptr;
                case RenderAPI::API::OpenGL:    return refs::create_ref<OpenGLVertexArray>();
                case RenderAPI::API::DirectX:   EXW_ASSERT(false, "RenderAPI::DirectX is not supported."); return nullptr;
                case RenderAPI::API::Vulkan:    EXW_ASSERT(false, "RenderAPI::Vulkan is not supported."); return nullptr;
            }

            EXW_ASSERT(false, "Unknown RenderAPI is not supported.");
            return nullptr;
        }
    }
}
