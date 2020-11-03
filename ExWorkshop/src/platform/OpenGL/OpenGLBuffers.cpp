// ;
#include "expch.h"
#include "OpenGLBuffers.h"

#include <glad\glad.h>

namespace exw
{
    namespace graphics
    {
        OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t _size)
        {
            EXW_PROFILE_FUNCTION();
            glCreateBuffers(1, &m_Renderer_id);
            glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_id);
            glBufferData(GL_ARRAY_BUFFER, _size, nullptr, GL_DYNAMIC_DRAW);
        }

        OpenGLVertexBuffer::OpenGLVertexBuffer(float* _vertices, uint32_t _size)
        {
            EXW_PROFILE_FUNCTION();
            glCreateBuffers(1, &m_Renderer_id);
            glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_id);
            glBufferData(GL_ARRAY_BUFFER, _size, _vertices, GL_STATIC_DRAW); // TODO: dynamic draw?;
        }

        OpenGLVertexBuffer::~OpenGLVertexBuffer()
        {
            EXW_PROFILE_FUNCTION();
            glDeleteBuffers(1, &m_Renderer_id);
        }

        void OpenGLVertexBuffer::bind() const
        {
            EXW_PROFILE_FUNCTION();
            glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_id);
        }

        void OpenGLVertexBuffer::unbind() const
        {
            EXW_PROFILE_FUNCTION();
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void OpenGLVertexBuffer::set_data(const void* _data, uint32_t _size)
        {
            //EXW_PROFILE_FUNCTION();
            glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_id);
            glBufferSubData(GL_ARRAY_BUFFER, 0, _size, _data);
        }

        OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* _indices, uint32_t _count)
            : m_Count(_count)
        {
            EXW_PROFILE_FUNCTION();
            glCreateBuffers(1, &m_Renderer_id);

            // GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
            // Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state.
            glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_id);
            glBufferData(GL_ARRAY_BUFFER, _count * sizeof(uint32_t), _indices, GL_STATIC_DRAW);
        }

        OpenGLIndexBuffer::~OpenGLIndexBuffer()
        {
            EXW_PROFILE_FUNCTION();
            glDeleteBuffers(1, &m_Renderer_id);
        }

        void OpenGLIndexBuffer::bind() const
        {
            EXW_PROFILE_FUNCTION();
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer_id);
        }
        void OpenGLIndexBuffer::unbind() const
        {
            EXW_PROFILE_FUNCTION();
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }
}
