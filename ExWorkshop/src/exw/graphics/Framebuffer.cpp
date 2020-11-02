#pragma once
// ;
#include "expch.h"
#include "Framebuffer.h"

#include "exw\graphics\RenderAPI.h"

#include "platform\OpenGL\OpenGLFramebuffer.h"

namespace exw
{
    namespace graphics
    {
        refs::ref<Framebuffer> Framebuffer::create(const FramebufferSpec& _spec)
        {
            switch (RenderAPI::get())
            {
                case RenderAPI::API::None:      EXW_ASSERT(false, "RenderAPI::None is not supported."); return nullptr;
                case RenderAPI::API::OpenGL:    return refs::create_ref<OpenGLFramebuffer>(_spec);
                case RenderAPI::API::DirectX:   EXW_ASSERT(false, "RenderAPI::DirectX is not supported."); return nullptr;
                case RenderAPI::API::Vulkan:    EXW_ASSERT(false, "RenderAPI::Vulkan is not supported."); return nullptr;

            }

            EXW_ASSERT(false, "Unknown Render API is not supported.");
            return nullptr;
        }
    }
}
