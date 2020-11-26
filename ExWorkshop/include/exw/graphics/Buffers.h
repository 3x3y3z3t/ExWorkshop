// ;
#pragma once

#include "exw\Common.h"

namespace exw
{
    namespace graphics
    {
        enum class ShaderDataType
        {
            None = 0,
            Bool,
            Int, Int2, Int3, Int4,
            Float, Float2, Float3, Float4,
            Mat3x3, Mat4x4,
        };

        static uint32_t shader_datatype_size(ShaderDataType _type)
        {
            switch (_type)
            {
                case exw::graphics::ShaderDataType::Bool:       return 1;
                case exw::graphics::ShaderDataType::Int:        return 4;
                case exw::graphics::ShaderDataType::Int2:       return 4 * 2;
                case exw::graphics::ShaderDataType::Int3:       return 4 * 3;
                case exw::graphics::ShaderDataType::Int4:       return 4 * 4;
                case exw::graphics::ShaderDataType::Float:      return 4;
                case exw::graphics::ShaderDataType::Float2:     return 4 * 2;
                case exw::graphics::ShaderDataType::Float3:     return 4 * 3;
                case exw::graphics::ShaderDataType::Float4:     return 4 * 4;
                case exw::graphics::ShaderDataType::Mat3x3:     return 4 * 3 * 3;
                case exw::graphics::ShaderDataType::Mat4x4:     return 4 * 4 * 4;
            }

            EXW_ASSERT(false, "Unknown Shader data type is not supported.");
            return 0;
        }

        struct BufferElement
        {
            std::string name;
            ShaderDataType type;
            uint32_t size;
            size_t offset;
            bool normalized;

            BufferElement() = default;

            BufferElement(ShaderDataType _type, const std::string& _name, bool _normalized = false)
                : type(_type), name(_name), normalized(_normalized), size(shader_datatype_size(type)), offset(0)
            {}

            uint32_t get_component_count() const
            {
                switch (type)
                {
                    case exw::graphics::ShaderDataType::Bool:       return 1;
                    case exw::graphics::ShaderDataType::Int:        return 1;
                    case exw::graphics::ShaderDataType::Int2:       return 2;
                    case exw::graphics::ShaderDataType::Int3:       return 3;
                    case exw::graphics::ShaderDataType::Int4:       return 4;
                    case exw::graphics::ShaderDataType::Float:      return 1;
                    case exw::graphics::ShaderDataType::Float2:     return 2;
                    case exw::graphics::ShaderDataType::Float3:     return 3;
                    case exw::graphics::ShaderDataType::Float4:     return 4;
                    case exw::graphics::ShaderDataType::Mat3x3:     return 3;
                    case exw::graphics::ShaderDataType::Mat4x4:     return 4;
                }

                EXW_ASSERT(false, "Unknown Shader data type is not supported.");
                return 0;
            }
        };

        class BufferLayout
        {
        public:
            BufferLayout() {}

            BufferLayout(const std::initializer_list<BufferElement>& _elements)
                : m_Elements(_elements)
            {
                calculate_offset_and_stride();
            }

        private:
            void calculate_offset_and_stride()
            {
                size_t offs = 0;
                m_Stride = 0;
                for (auto& element : m_Elements)
                {
                    element.offset = offs;
                    offs += element.size;
                    m_Stride += element.size;
                }
            }
        public:
            inline uint32_t get_stride() const { return m_Stride; }
            inline const std::vector<BufferElement>& get_elements() const { return m_Elements; }

            std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
            std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
            std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
            std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

        private:
            std::vector<BufferElement> m_Elements;
            uint32_t m_Stride = 0;
        };

        class VertexBuffer
        {
        public:
            virtual ~VertexBuffer() = default;

        public:
            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual const BufferLayout& get_layout() const = 0;

            virtual void set_layout(const BufferLayout& _bufferLayout) = 0;
            virtual void set_data(const void* _data, uint32_t _size) = 0;

            static refs::ref<VertexBuffer> create(uint32_t _size);
            static refs::ref<VertexBuffer> create(float* _vertices, uint32_t _size);
        };

        class IndexBuffer
        {
        public:
            virtual ~IndexBuffer() = default;

        public:
            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual uint32_t count() const = 0;

            static refs::ref<IndexBuffer> create(uint32_t* _indices, uint32_t _count);
        };
    }
}
