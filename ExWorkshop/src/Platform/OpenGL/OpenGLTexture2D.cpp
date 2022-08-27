/*  OpenGLTexture2D.cpp
*   Version: 1.0 (2022.08.27)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "OpenGLTexture2D.h"

#include "exw\utils\Logger.h"

#include <stb_image.h>

namespace exw
{
    namespace graphics
    {
        OpenGLTexture2D::OpenGLTexture2D(uint32_t _width, uint32_t _height)
            : m_Width(_width), m_Height(_height)
        {
            m_Internal_format = GL_RGBA8;
            m_Data_format = GL_RGBA8;

            glCreateTextures(GL_TEXTURE_2D, 1, &m_Renderer_id);
            glTextureStorage2D(m_Renderer_id, 1, m_Internal_format, m_Width, m_Height);

            glTextureParameteri(m_Renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTextureParameteri(m_Renderer_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTextureParameteri(m_Renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(m_Renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }

        OpenGLTexture2D::OpenGLTexture2D(const std::string& _filepath)
            : m_Filepath(_filepath)
        {
            int width = 0;
            int height = 0;
            int channels = 0;

            stbi_set_flip_vertically_on_load(1);
            stbi_uc* data = nullptr;
            {
                data = stbi_load(_filepath.c_str(), &width, &height, &channels, 0);
            }

            if (data == nullptr)
            {
                EXW_LOG_CORE_ERROR("Could not load texture {0}", m_Filepath);
                return;
            }

            m_Width = width;
            m_Height = height;

            if (channels == 4)
            {
                m_Internal_format = GL_RGBA8;
                m_Data_format = GL_RGBA;
            }
            else if (channels == 3)
            {
                m_Internal_format = GL_RGB8;
                m_Data_format = GL_RGB;
            }
            else
            {
                EXW_LOG_CORE_ERROR("Format not supported (channels = {0}).", channels);
                stbi_image_free(data);
                return;
            }
            //EXW_ASSERT_CORE(m_Internal_format == 0 && m_Data_format == 0, "Format not supported.");

            m_Is_loaded = true;

            glCreateTextures(GL_TEXTURE_2D, 1, &m_Renderer_id);
            glTextureStorage2D(m_Renderer_id, 1, m_Internal_format, width, height);

            glTextureParameteri(m_Renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTextureParameteri(m_Renderer_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTextureParameteri(m_Renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(m_Renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glTextureSubImage2D(m_Renderer_id, 0, 0, 0, width, height, m_Data_format, GL_UNSIGNED_BYTE, data);

            stbi_image_free(data);
        }

        OpenGLTexture2D::~OpenGLTexture2D()
        {
            glDeleteTextures(1, &m_Renderer_id);
        }

        void OpenGLTexture2D::bind(uint32_t _slot) const
        {
            glBindTextureUnit(_slot, m_Renderer_id);
        }

        void OpenGLTexture2D::set_data(void* _data, uint32_t _size)
        {
            uint32_t bpp = m_Data_format == GL_RGBA ? 4 : 3;
            if (_size != m_Width * m_Height * bpp)
            {
                EXW_LOG_CORE_ERROR("Data size and texture size mismatch (_size = {0}; m_Width = {1}, m_Height = {2}, bpp = {3}).", _size, m_Width, m_Height, bpp);
                return;
            }

            glTextureSubImage2D(m_Renderer_id, 0, 0, 0, m_Width, m_Height, m_Data_format, GL_UNSIGNED_BYTE, _data);
        }

    }
}
