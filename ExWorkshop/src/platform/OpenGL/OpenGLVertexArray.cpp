// ;
#include "expch.h"
#include "OpenGLVertexArray.h"

#include "exw\graphics\Buffers.h"

//#include <GLFW\glfw3.h>
#include <glad\glad.h>

namespace exw
{
    namespace graphics
    {
        static GLenum shader_datatype_to_opengl_type(ShaderDataType _type)
        {
            switch (_type)
            {
                case exw::graphics::ShaderDataType::Bool:       return GL_BOOL;
                case exw::graphics::ShaderDataType::Int:        return GL_INT;
                case exw::graphics::ShaderDataType::Int2:       return GL_INT;
                case exw::graphics::ShaderDataType::Int3:       return GL_INT;
                case exw::graphics::ShaderDataType::Int4:       return GL_INT;
                case exw::graphics::ShaderDataType::Float:      return GL_FLOAT;
                case exw::graphics::ShaderDataType::Float2:     return GL_FLOAT;
                case exw::graphics::ShaderDataType::Float3:     return GL_FLOAT;
                case exw::graphics::ShaderDataType::Float4:     return GL_FLOAT;
                case exw::graphics::ShaderDataType::Mat3x3:     return GL_FLOAT;
                case exw::graphics::ShaderDataType::Mat4x4:     return GL_FLOAT;
            }

            EXW_ASSERT(false, "Unknown Shader data type is not supported.");
            return 0;
        }

        OpenGLVertexArray::OpenGLVertexArray()
        {
            EXW_PROFILE_FUNCTION();
            glCreateVertexArrays(1, &m_Renderer_id);
        }

        OpenGLVertexArray::~OpenGLVertexArray()
        {
            EXW_PROFILE_FUNCTION();
            glDeleteVertexArrays(1, &m_Renderer_id);
        }

        void OpenGLVertexArray::bind() const
        {
            EXW_PROFILE_FUNCTION();
            glBindVertexArray(m_Renderer_id);
        }

        void OpenGLVertexArray::unbind() const
        {
            EXW_PROFILE_FUNCTION();
            glBindVertexArray(0);
        }

        void OpenGLVertexArray::add_vertex_buffer(const refs::ref<VertexBuffer>& _vertexBuffer)
        {
            EXW_PROFILE_FUNCTION();
            EXW_ASSERT(_vertexBuffer->get_layout().get_elements().size() != 0U, "This Vertex buffer has no layout!");

            glBindVertexArray(m_Renderer_id);
            _vertexBuffer->bind();
            const auto& layout = _vertexBuffer->get_layout();
            for (const auto& element : layout)
            {
                switch (element.type)
                {
                    case exw::graphics::ShaderDataType::Bool:
                    case exw::graphics::ShaderDataType::Int:
                    case exw::graphics::ShaderDataType::Int2:
                    case exw::graphics::ShaderDataType::Int3:
                    case exw::graphics::ShaderDataType::Int4:
                    case exw::graphics::ShaderDataType::Float:
                    case exw::graphics::ShaderDataType::Float2:
                    case exw::graphics::ShaderDataType::Float3:
                    case exw::graphics::ShaderDataType::Float4:
                    {
                        glEnableVertexAttribArray(m_Vertex_buffer_index);
                        glVertexAttribPointer(
                            m_Vertex_buffer_index,
                            element.get_component_count(),
                            shader_datatype_to_opengl_type(element.type),
                            element.normalized ? GL_TRUE : GL_FALSE,
                            layout.get_stride(),
                            (const void*)element.offset
                        );
                        ++m_Vertex_buffer_index;
                        break;
                    }
                    case exw::graphics::ShaderDataType::Mat3x3:
                    case exw::graphics::ShaderDataType::Mat4x4:
                    {
                        uint8_t count = element.get_component_count();
                        for (uint8_t i = 0U; i < count; ++i)
                        {
                            glEnableVertexAttribArray(m_Vertex_buffer_index);
                            glVertexAttribPointer(
                                m_Vertex_buffer_index,
                                count,
                                shader_datatype_to_opengl_type(element.type),
                                element.normalized ? GL_TRUE : GL_FALSE,
                                layout.get_stride(),
                                (const void*)(element.offset + sizeof(float) * count * i)
                            );
                            glVertexAttribDivisor(m_Vertex_buffer_index, 1);
                            ++m_Vertex_buffer_index;
                        }
                        break;
                    }
                    default:
                        EXW_ASSERT(false, "Unknown Shader data type is not supported.");
                }
            }

            m_Vertex_buffers.push_back(_vertexBuffer);
        }

        void OpenGLVertexArray::set_index_buffer(const refs::ref<IndexBuffer>& _indexBuffer)
        {
            EXW_PROFILE_FUNCTION();
            glBindVertexArray(m_Renderer_id);
            _indexBuffer->bind();
            m_Index_buffer = _indexBuffer;
        }
    }
}
