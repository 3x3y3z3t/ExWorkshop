/*  OpenGLBuffers.h
*   Version: 1.0 (2022.07.23)
*
*   Contributor
*       Arime-chan
*/
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

            virtual void bind() const override;
            virtual void unbind() const override;

            virtual const BufferLayout& get_layout() const override { return m_Layout; }

            virtual void set_data(const void* _data, uint32_t _size) override;
            virtual void set_layout(const BufferLayout& _layout) override { m_Layout = _layout; }

        private:
            uint32_t m_Renderer_id = 0U;
            BufferLayout m_Layout;
        };

        class OpenGLIndexBuffer : public IndexBuffer
        {
        public:
            OpenGLIndexBuffer(uint32_t* _indices, uint32_t _count);
            virtual ~OpenGLIndexBuffer();

            virtual void bind() const override;
            virtual void unbind() const override;

            virtual uint32_t get_count() const override { return m_Count; }

        private:
            uint32_t m_Renderer_id = 0U;
            uint32_t m_Count = 0U;
        };

    }
}
