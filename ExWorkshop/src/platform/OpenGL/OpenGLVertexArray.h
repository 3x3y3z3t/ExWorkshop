// ;
#pragma once

#include "exw\graphics\VertexArray.h"

namespace exw
{
    namespace graphics
    {
        class OpenGLVertexArray : public VertexArray
        {
        public:
            OpenGLVertexArray();
            virtual ~OpenGLVertexArray();

        public:
            virtual void bind() const override;
            virtual void unbind() const override;

            virtual const std::vector<refs::ref<VertexBuffer>>& get_vertex_buffers() const override { return m_Vertex_buffers; }
            virtual const refs::ref<IndexBuffer>& get_index_buffer() const override { return m_Index_buffer; }

            virtual void add_vertex_buffer(const refs::ref<VertexBuffer>& _vertexBuffer) override;
            virtual void set_index_buffer(const refs::ref<IndexBuffer>& _indexBuffer) override;

        private:
            uint32_t m_Renderer_id;
            uint32_t m_Vertex_buffer_index = 0;
            std::vector<refs::ref<VertexBuffer>> m_Vertex_buffers;
            refs::ref<IndexBuffer> m_Index_buffer;
        };
    }
}



/*
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
*/
