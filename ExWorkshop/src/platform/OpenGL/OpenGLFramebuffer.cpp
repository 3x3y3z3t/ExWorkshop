// ;
#include "expch.h"
#include "OpenGLFramebuffer.h"

#include <glad\glad.h>

namespace exw
{
    namespace graphics
    {
        static const uint32_t s_Max_framebuffer_size = 8192;

        OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpec& _spec)
            : m_Spec(_spec)
        {
            invalidate();
        }

        OpenGLFramebuffer::~OpenGLFramebuffer()
        {
            glDeleteFramebuffers(1, &m_Renderer_id);
            glDeleteTextures(1, &m_Color_attachment);
            glDeleteTextures(1, &m_Depth_attachment);
        }

        void OpenGLFramebuffer::invalidate()
        {
            if (m_Renderer_id != 0U)
            {
                glDeleteFramebuffers(1, &m_Renderer_id);
                glDeleteTextures(1, &m_Color_attachment);
                glDeleteTextures(1, &m_Depth_attachment);
            }

            glCreateFramebuffers(1, &m_Renderer_id);
            glBindFramebuffer(GL_FRAMEBUFFER, m_Renderer_id);

            glCreateTextures(GL_TEXTURE_2D, 1, &m_Color_attachment);
            glBindTexture(GL_TEXTURE_2D, m_Color_attachment);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Spec.Width, m_Spec.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Color_attachment, 0);

            glCreateTextures(GL_TEXTURE_2D, 1, &m_Depth_attachment);
            glBindTexture(GL_TEXTURE_2D, m_Depth_attachment);
            glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Spec.Width, m_Spec.Height);
            //glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Spec.Width, m_Spec.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr); // fallback;
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_Depth_attachment, 0);

            EXW_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete.");

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void OpenGLFramebuffer::bind()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, m_Renderer_id);
            glViewport(0, 0, m_Spec.Width, m_Spec.Height);
        }

        void OpenGLFramebuffer::unbind()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void OpenGLFramebuffer::resize(uint32_t _width, uint32_t _height)
        {
            if (_width == 0 || _height == 0 || _width > s_Max_framebuffer_size || _height > s_Max_framebuffer_size)
            {
                EXW_LOG_WARNING("Attempted to resize framebuffer to ({0}, {1})", _width, _height);
                return;
            }

            m_Spec.Width = _width;
            m_Spec.Height = _height;
            invalidate();
        }
    }
}
