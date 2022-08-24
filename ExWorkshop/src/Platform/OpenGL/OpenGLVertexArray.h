/*  OpenGLVertexArray.h
*   Version: 1.0 (2022.07.24)
*
*   Contributor
*       Arime-chan
*/
#pragma once
#include "exwpch.h"

#include "exw\graphics\VertexArray.h"
#include "exw\graphics\Buffers.h"

namespace exw
{
    namespace graphics
    {
        class OpenGLVertexArray : public VertexArray
        {
        public:
            OpenGLVertexArray();
            virtual ~OpenGLVertexArray();

            virtual void bind() const override;
            virtual void unbind() const override;

            virtual const std::vector<refs::Ref<VertexBuffer>>& get_vertex_buffers() const override { return m_Vertex_buffers; }
            virtual const refs::Ref<IndexBuffer>& get_index_buffer() const override { return m_Index_buffer; }

            virtual void add_vertex_buffer(const refs::Ref<VertexBuffer>& _vertexBuffer) override;
            virtual void set_index_buffer(const refs::Ref<IndexBuffer>& _indexBuffer) override;

        private:
            uint32_t m_Renderer_id = 0U;
            uint32_t m_Vertex_buffer_index = 0U;
            std::vector<refs::Ref<VertexBuffer>> m_Vertex_buffers;
            refs::Ref<IndexBuffer> m_Index_buffer;
        };

    }
}
