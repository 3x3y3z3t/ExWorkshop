// ;
#include "expch.h"
#include "GraphicsContext.h"

#include "exw\graphics\RenderAPI.h"

#include "platform\OpenGL\OpenGLGraphicsContext.h"

namespace exw
{
    namespace graphics
    {
        refs::scope<GraphicsContext> GraphicsContext::create(void* _window)
        {
            switch (RenderAPI::get())
            {
                case RenderAPI::API::None:      EXW_ASSERT(false, "RenderAPI::None is not supported."); return nullptr;
                case RenderAPI::API::OpenGL:    return refs::create_scoped<OpenGLGraphicsContext>(static_cast<GLFWwindow*>(_window));
                case RenderAPI::API::DirectX:   EXW_ASSERT(false, "RenderAPI::DirectX is not supported."); return nullptr;
                case RenderAPI::API::Vulkan:    EXW_ASSERT(false, "RenderAPI::Vulkan is not supported."); return nullptr;
            }

            EXW_ASSERT(false, "Unknown Render API is not supported.");
            return nullptr;
        }
    }
}
