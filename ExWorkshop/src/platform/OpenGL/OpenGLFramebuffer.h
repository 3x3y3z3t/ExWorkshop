// ;
#pragma once

#include "exw\graphics\Framebuffer.h"

namespace exw
{
    namespace graphics
    {
        class OpenGLFramebuffer : public Framebuffer
        {
        public:
            OpenGLFramebuffer(const FramebufferSpec& _spec);
            virtual ~OpenGLFramebuffer();

        public:
            void invalidate();
            virtual void bind() override;
            virtual void unbind() override;

            virtual void resize(uint32_t _width, uint32_t _height) override;

            virtual uint32_t get_color_attachment_renderer_id() const override { return m_Color_attachment; }
            virtual FramebufferSpec& get_spec() override { return m_Spec; }
            virtual const FramebufferSpec& get_spec() const override { return m_Spec; }

        private:
            uint32_t m_Renderer_id = 0U;
            uint32_t m_Color_attachment = 0U;
            uint32_t m_Depth_attachment = 0U;
            FramebufferSpec m_Spec;
        };
    }
}
