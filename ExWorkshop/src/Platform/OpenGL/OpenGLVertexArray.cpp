/*  OpenGLVertexArray.cpp
*   Version: 1.0 (2022.07.24)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "OpenGLVertexArray.h"

#include "exw\utils\Logger.h"

#include <glad\gl.h>

namespace exw
{
    namespace graphics
    {
        GLenum shader_data_type_to_opengl_base_type(ShaderDataType _type)
        {
            switch (_type)
            {
                case exw::graphics::ShaderDataType::Bool:           return GL_BOOL;
                case exw::graphics::ShaderDataType::Int:            return GL_INT;
                case exw::graphics::ShaderDataType::Int2:           return GL_INT;
                case exw::graphics::ShaderDataType::Int3:           return GL_INT;
                case exw::graphics::ShaderDataType::Int4:           return GL_INT;
                case exw::graphics::ShaderDataType::Float:          return GL_FLOAT;
                case exw::graphics::ShaderDataType::Float2:         return GL_FLOAT;
                case exw::graphics::ShaderDataType::Float3:         return GL_FLOAT;
                case exw::graphics::ShaderDataType::Float4:         return GL_FLOAT;
                case exw::graphics::ShaderDataType::Matrix3:        return GL_FLOAT;
                case exw::graphics::ShaderDataType::Matrix4:        return GL_FLOAT;
            }

            EXW_ASSERT_CORE(false, "ShaderDataType {0} is not supported.", (uint32_t)_type);
            return 0U;
        }

        OpenGLVertexArray::OpenGLVertexArray()
        {
            glCreateVertexArrays(1, &m_Renderer_id);
        }

        OpenGLVertexArray::~OpenGLVertexArray()
        {
            glDeleteVertexArrays(1, &m_Renderer_id);
        }

        void OpenGLVertexArray::bind() const
        {
            glBindVertexArray(m_Renderer_id);
        }

        void OpenGLVertexArray::unbind() const
        {
            glBindVertexArray(0U);
        }

        void OpenGLVertexArray::add_vertex_buffer(const refs::Ref<VertexBuffer>&_vertexBuffer)
        {
            EXW_ASSERT_CORE(_vertexBuffer->get_layout().get_elements().size() != 0Ui64, "Vertex Buffer has no layout.");

            glBindVertexArray(m_Renderer_id);
            _vertexBuffer->bind();

            const auto& layout = _vertexBuffer->get_layout();
            for (const auto& element : layout)
            {
                switch (element.Type)
                {
                    case exw::graphics::ShaderDataType::Bool:
                    case exw::graphics::ShaderDataType::Int:
                    case exw::graphics::ShaderDataType::Int2:
                    case exw::graphics::ShaderDataType::Int3:
                    case exw::graphics::ShaderDataType::Int4:
                    {
                        glEnableVertexAttribArray(m_Vertex_buffer_index);
                        glVertexAttribIPointer(m_Vertex_buffer_index,
                                               element.get_component_count(),
                                               shader_data_type_to_opengl_base_type(element.Type),
                                               layout.get_stride(),
                                               (const void*)element.Offset);
                        m_Vertex_buffer_index++;
                        break;
                    }

                    case exw::graphics::ShaderDataType::Float:
                    case exw::graphics::ShaderDataType::Float2:
                    case exw::graphics::ShaderDataType::Float3:
                    case exw::graphics::ShaderDataType::Float4:
                    {
                        glEnableVertexAttribArray(m_Vertex_buffer_index);
                        glVertexAttribPointer(m_Vertex_buffer_index,
                                               element.get_component_count(),
                                               shader_data_type_to_opengl_base_type(element.Type),
                                               element.Normalized ? GL_TRUE : GL_FALSE,
                                               layout.get_stride(),
                                               (const void*)element.Offset);
                        m_Vertex_buffer_index++;
                        break;
                    }

                    case exw::graphics::ShaderDataType::Matrix3:
                    case exw::graphics::ShaderDataType::Matrix4:
                    {
                        uint8_t count = (uint8_t)element.get_component_count();
                        for (uint8_t i = 0; i < count; ++i)
                        {
                            glEnableVertexAttribArray(m_Vertex_buffer_index);
                            glVertexAttribPointer(m_Vertex_buffer_index,
                                                   count,
                                                   shader_data_type_to_opengl_base_type(element.Type),
                                                   element.Normalized ? GL_TRUE : GL_FALSE,
                                                   layout.get_stride(),
                                                   (const void*)(element.Offset + sizeof(float) * count * i));
                            glVertexAttribDivisor(m_Vertex_buffer_index, 1U);
                            m_Vertex_buffer_index++;
                        }
                        break;
                    }

                    default: EXW_ASSERT_CORE(false, "ShaderDataType {0} is not supported.", (uint32_t)element.Type);
                }
            }

            m_Vertex_buffers.push_back(_vertexBuffer);
        }

        void OpenGLVertexArray::set_index_buffer(const refs::Ref<IndexBuffer>&_indexBuffer)
        {
            glBindVertexArray(m_Renderer_id);
            _indexBuffer->bind();
            m_Index_buffer = _indexBuffer;
        }

    }
}
