// ;
#pragma once

#include "exw\graphics\Buffers.h"

namespace exw
{
    namespace graphics
    {
        class OpenGLVertexBuffer : public VertexBuffer
        {
        public:
            OpenGLVertexBuffer(uint32_t _size);
            OpenGLVertexBuffer(float* _vertices, uint32_t _size);
            virtual ~OpenGLVertexBuffer();

        public:
            virtual void bind() const override;
            virtual void unbind() const override;

            virtual const BufferLayout& get_layout() const override { return m_Layout; }

            virtual void set_layout(const BufferLayout& _bufferLayout) override { m_Layout = _bufferLayout; }
            virtual void set_data(const void* _data, uint32_t _size) override;

        private:
            uint32_t m_Renderer_id;
            BufferLayout m_Layout;
        };

        class OpenGLIndexBuffer : public IndexBuffer
        {
        public:
            OpenGLIndexBuffer(uint32_t* _indices, uint32_t _count);
            virtual ~OpenGLIndexBuffer();

        public:
            virtual void bind() const override;
            virtual void unbind() const override;

            virtual uint32_t count() const { return m_Count; }

        private:
            uint32_t m_Renderer_id;
            uint32_t m_Count;
        };
    }
}
