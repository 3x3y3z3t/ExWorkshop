// ;
#pragma once

#include "exw\Common.h"
#include "Buffers.h"

namespace exw
{
    namespace graphics
    {
        class VertexArray
        {
        public:
            virtual ~VertexArray() = default;

        public:
            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual const std::vector<refs::ref<VertexBuffer>>& get_vertex_buffers() const = 0;
            virtual const refs::ref<IndexBuffer>& get_index_buffer() const = 0;

            virtual void add_vertex_buffer(const refs::ref<VertexBuffer>& _vertexBuffer) = 0;
            virtual void set_index_buffer(const refs::ref<IndexBuffer>& _indexBuffer) = 0;

            static refs::ref<VertexArray> create();
        };
    }
}
