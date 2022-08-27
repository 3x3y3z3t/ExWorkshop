/*  Texture.cpp
*   Version: 1.0 (2022.08.27)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "exw\utils\Logger.h"
#include "platform\OpenGL\OpenGLTexture2D.h"

namespace exw
{
    namespace graphics
    {
        refs::Ref<Texture2D> Texture2D::create(uint32_t _width, uint32_t _height)
        {
            RendererAPI::API activeApi = Renderer::get_active_api();
            switch (activeApi)
            {
                case RendererAPI::API::OpenGL:      return refs::create_ref<OpenGLTexture2D>(_width, _height);
            }

            EXW_LOG_CORE_CRITICAL("RendererAPI {0} is not supported.", (uint8_t)activeApi);
            EXW_ASSERT_CORE(false);
            return nullptr;
        }

        refs::Ref<Texture2D> Texture2D::create(const std::string& _filepath)
        {
            RendererAPI::API activeApi = Renderer::get_active_api();
            switch (activeApi)
            {
                case RendererAPI::API::OpenGL:      return refs::create_ref<OpenGLTexture2D>(_filepath);
            }

            EXW_LOG_CORE_CRITICAL("RendererAPI {0} is not supported.", (uint8_t)activeApi);
            EXW_ASSERT_CORE(false);
            return nullptr;
        }

    }
}
