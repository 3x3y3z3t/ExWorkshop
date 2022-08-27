/*  OpenGLTexture2D.h
*   Version: 1.0 (2022.08.27)
*
*   Contributor
*       Arime-chan
*/
#pragma once

#include "exw\graphics\Texture.h"

#include <glad\gl.h>

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

            virtual void bind(uint32_t _slot = 0) const override;

            virtual bool is_loaded() const override { return m_Is_loaded; }
            virtual uint32_t get_width() const override { return m_Width; }
            virtual uint32_t get_height() const override { return m_Height; }
            virtual uint32_t get_renderer_id() const override { return m_Renderer_id; }

            virtual const std::string& get_filepath() const override { return m_Filepath; }

            virtual void set_data(void* _data, uint32_t _size) override;

            virtual bool operator==(const Texture& _other) const override { return m_Renderer_id == _other.get_renderer_id(); }

        private:
            std::string m_Filepath;

            bool m_Is_loaded = false;
            uint32_t m_Width = 0U;
            uint32_t m_Height = 0U;

            uint32_t m_Renderer_id = 0U;

            GLenum m_Internal_format = 0U;
            GLenum m_Data_format = 0U;

        };

    }
}
