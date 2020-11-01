// ;
#include "expch.h"
#include "RenderAPI.h"

#include "platform\OpenGL\OpenGLRenderAPI.h"

namespace exw
{
    namespace graphics
    {
        RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;

        refs::scope<RenderAPI> exw::graphics::RenderAPI::create()
        {
            switch (s_API)
            {
                case RenderAPI::API::None:      EXW_ASSERT(false, "RenderAPI::None is not supported."); return nullptr;
                case RenderAPI::API::OpenGL:    return refs::create_scoped<OpenGLRenderAPI>();
                case RenderAPI::API::DirectX:   EXW_ASSERT(false, "RenderAPI::DirectX is not supported."); return nullptr;
                case RenderAPI::API::Vulkan:    EXW_ASSERT(false, "RenderAPI::Vulkan is not supported."); return nullptr;
            }

            EXW_ASSERT(false, "Unknown RenderAPI is not supported.");
            return nullptr;
        }
    }
}
