// ;
#pragma once

#include "exw\Common.h"

namespace exw
{
    namespace graphics
    {
        enum class FramebufferFormat
        {
            None = 0,
        };

        struct FramebufferSpec
        {
            uint32_t Width = 0U;
            uint32_t Height = 0U;
            FramebufferFormat Format = FramebufferFormat::None;
            uint32_t Samples = 1U;
            bool SwapChainTarget = false;
        };

        class Framebuffer
        {
        public:
            virtual ~Framebuffer() = default;

        public:
            virtual void bind() = 0;
            virtual void unbind() = 0;

            virtual void resize(uint32_t _width, uint32_t _height) = 0;

            virtual uint32_t get_color_attachment_renderer_id() const = 0;
            virtual const FramebufferSpec& get_spec() const = 0;
            virtual FramebufferSpec& get_spec() = 0;

            static refs::ref<Framebuffer> create(const FramebufferSpec& _spec);

        };
    }
}
