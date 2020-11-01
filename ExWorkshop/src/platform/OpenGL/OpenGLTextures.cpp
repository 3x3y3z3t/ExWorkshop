// ;
#include "expch.h"
#include "OpenGLTextures.h"

#include "exw\Common.h"

#include <stb_image.h>

namespace exw
{
    namespace graphics
    {
        OpenGLTexture2D::OpenGLTexture2D(uint32_t _width, uint32_t _height)
            : m_Width(_width), m_Height(_height)
        {
            m_Internal_format = GL_RGBA8;
            m_Data_format = GL_RGBA;

            glCreateTextures(GL_TEXTURE_2D, 1, &m_Renderer_id);
            glTextureStorage2D(m_Renderer_id, 1, m_Internal_format, _width, _height);

            glTextureParameteri(m_Renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTextureParameteri(m_Renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTextureParameteri(m_Renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(m_Renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }

        OpenGLTexture2D::OpenGLTexture2D(const std::string& _filepath)
            : m_Filepath(_filepath)
        {
            int w, h, c;
            stbi_set_flip_vertically_on_load(1);
            stbi_uc* data = stbi_load(_filepath.c_str(), &w, &h, &c, 0);

            EXW_ASSERT(data, "Image load failure.");
            m_Width = w;
            m_Height = h;

            GLenum internalFormat = 0, dataFormat = 0;
            if (c == 4)
            {
                internalFormat = GL_RGBA8;
                dataFormat = GL_RGBA;
            }
            else if (c == 3)
            {
                internalFormat = GL_RGB8;
                dataFormat = GL_RGB;
            }
            EXW_ASSERT(internalFormat & dataFormat, "This format is not supported.");

            m_Internal_format = internalFormat;
            m_Data_format = dataFormat;

            glCreateTextures(GL_TEXTURE_2D, 1, &m_Renderer_id);
            glTextureStorage2D(m_Renderer_id, 1, internalFormat, w, h);

            glTextureParameteri(m_Renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTextureParameteri(m_Renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTextureParameteri(m_Renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(m_Renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glTextureSubImage2D(m_Renderer_id, 0, 0, 0, w, h, dataFormat, GL_UNSIGNED_BYTE, data);

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
            EXW_ASSERT(_size == m_Width * m_Height * bpp, "Partial textured data is not supported.");
            glTextureSubImage2D(m_Renderer_id, 0, 0, 0, m_Width, m_Height, m_Data_format, GL_UNSIGNED_BYTE, _data);
        }
    }
}
