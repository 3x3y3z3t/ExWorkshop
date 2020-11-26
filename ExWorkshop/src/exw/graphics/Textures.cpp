// ;
#include "expch.h"
#include "exw\graphics\Textures.h"

#include "exw\graphics\RenderAPI.h"

#include "platform\OpenGL\OpenGLTextures.h"

namespace exw
{
    namespace graphics
    {
        refs::ref<Texture2D> Texture2D::create(uint32_t _width, uint32_t _height)
        {
            switch (RenderAPI::get())
            {
                case RenderAPI::API::None:      EXW_ASSERT(false, "RenderAPI::None is not supported."); return nullptr;
                case RenderAPI::API::OpenGL:    return refs::create_scoped<OpenGLTexture2D>(_width, _height);
                case RenderAPI::API::DirectX:   EXW_ASSERT(false, "RenderAPI::DirectX is not supported."); return nullptr;
                case RenderAPI::API::Vulkan:    EXW_ASSERT(false, "RenderAPI::Vulkan is not supported."); return nullptr;
            }

            EXW_ASSERT(false, "Unknown RenderAPI is not supported.");
            return nullptr;
        }

        refs::ref<Texture2D> Texture2D::create(const std::string& _filepath)
        {
            switch (RenderAPI::get())
            {
                case RenderAPI::API::None:      EXW_ASSERT(false, "RenderAPI::None is not supported."); return nullptr;
                case RenderAPI::API::OpenGL:    return refs::create_scoped<OpenGLTexture2D>(_filepath);
                case RenderAPI::API::DirectX:   EXW_ASSERT(false, "RenderAPI::DirectX is not supported."); return nullptr;
                case RenderAPI::API::Vulkan:    EXW_ASSERT(false, "RenderAPI::Vulkan is not supported."); return nullptr;
            }

            EXW_ASSERT(false, "Unknown RenderAPI is not supported.");
            return nullptr;
        }
    }
}
