/*  VertexArray.h
*   Version: 1.0 (2022.07.24)
*
*   Contributor
*       Arime-chan
*/
#pragma once
#include "exwpch.h"

#include "Buffers.h"
#include "exw\Common.h"

namespace exw
{
    namespace graphics
    {
        class VertexArray
        {
        public:
            virtual ~VertexArray() = default;

            static refs::Ref<VertexArray> create();

            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual const std::vector<refs::Ref<VertexBuffer>>& get_vertex_buffers() const = 0;
            virtual const refs::Ref<IndexBuffer>& get_index_buffer() const = 0;

            virtual void add_vertex_buffer(const refs::Ref<VertexBuffer>& _vertexBuffer) = 0;
            virtual void set_index_buffer(const refs::Ref<IndexBuffer>& _indexBuffer) = 0;
        };

    }
}
