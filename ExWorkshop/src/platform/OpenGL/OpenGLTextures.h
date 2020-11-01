// ;
#pragma once

#include "exw\graphics\Textures.h"

#include <glad\glad.h>

namespace exw
{
    namespace graphics
    {
        class OpenGLTexture2D : public Texture2D
        {
        public:
            OpenGLTexture2D(uint32_t _width, uint32_t _height);
            OpenGLTexture2D(const std::string& _filepath);
            virtual ~OpenGLTexture2D();

        public:
            virtual void bind(uint32_t _slot = 0) const override;

            virtual uint32_t get_renderer_id() const override { return m_Renderer_id; }
            virtual uint32_t get_width() const override { return m_Width; }
            virtual uint32_t get_height() const override { return m_Height; }

            virtual void set_data(void* _data, uint32_t _size) override;

            virtual bool operator==(const Texture& _texture) const override { return m_Renderer_id == ((OpenGLTexture2D&)_texture).m_Renderer_id; }

        private:
            uint32_t m_Renderer_id;
            uint32_t m_Width;
            uint32_t m_Height;
            GLenum m_Internal_format;
            GLenum m_Data_format;
            std::string m_Filepath;
        };
    }
}
