/*  Buffers.h
*   Version: 1.0 (2022.07.23)
* 
*   Contributor
*       Arime-chan
*/
#pragma once

#include "exw\Common.h"

#include "exw\utils\Logger.h"

namespace exw
{
    namespace graphics
    {
        enum class ShaderDataType : uint32_t
        {
            None = 0,
            Bool, Int, Int2, Int3, Int4, Float, Float2, Float3, Float4, Matrix3, Matrix4
        };

        inline static constexpr uint32_t shader_data_type_size(ShaderDataType _type);

        struct BufferElement
        {
            std::string Name;
            ShaderDataType Type = ShaderDataType::None;
            uint32_t Size = 0U;
            size_t Offset = 0Ui64;
            bool Normalized = false;

            BufferElement() = default;
            inline BufferElement(ShaderDataType _type, const std::string& _name, bool _normalized = false);

            inline uint32_t get_component_count() const;
        };

        class BufferLayout
        {
        public:
            BufferLayout() {}
            inline BufferLayout(std::initializer_list<BufferElement> _elements);

            uint32_t get_stride() const { return m_Stride; }
            const std::vector<BufferElement>& get_elements() const { return m_Elements; }

            std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
            std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
            std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
            std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
        private:
            inline void calculate_offset_and_stride();

        private:
            std::vector<BufferElement> m_Elements;
            uint32_t m_Stride = 0U;
        };


        class VertexBuffer
        {
        public:
            virtual ~VertexBuffer() = default;

            static refs::Ref<VertexBuffer> create(uint32_t _size);
            static refs::Ref<VertexBuffer> create(float* _vertices, uint32_t _size);

            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual const BufferLayout& get_layout() const = 0;

            virtual void set_data(const void* _data, uint32_t _size) = 0;
            virtual void set_layout(const BufferLayout& _layout) = 0;
        };

        class IndexBuffer
        {
        public:
            virtual ~IndexBuffer() = default;

            static refs::Ref<IndexBuffer> create(uint32_t* _indices, uint32_t _count);

            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual uint32_t get_count() const = 0;
        };

    }
}

#pragma region Inline Definition
namespace exw
{
    namespace graphics
    {
        static constexpr uint32_t shader_data_type_size(ShaderDataType _type)
        {
            switch (_type)
            {
                case exw::graphics::ShaderDataType::Bool:       return 1U;
                case exw::graphics::ShaderDataType::Int:        return 4U;
                case exw::graphics::ShaderDataType::Int2:       return 4U * 2U;
                case exw::graphics::ShaderDataType::Int3:       return 4U * 3U;
                case exw::graphics::ShaderDataType::Int4:       return 4U * 4U;
                case exw::graphics::ShaderDataType::Float:      return 4U;
                case exw::graphics::ShaderDataType::Float2:     return 4U * 2U;
                case exw::graphics::ShaderDataType::Float3:     return 4U * 3U;
                case exw::graphics::ShaderDataType::Float4:     return 4U * 4U;
                case exw::graphics::ShaderDataType::Matrix3:    return 4U * 4U * 3U;
                case exw::graphics::ShaderDataType::Matrix4:    return 4U * 4U * 4U;
            }

            EXW_ASSERT_CORE(false, "ShaderDataType {0} is not supported.", (uint32_t)_type);
            return 0U;
        }

        BufferElement::BufferElement(ShaderDataType _type, const std::string& _name, bool _normalized)
            : Name(_name), Type(_type), Size(shader_data_type_size(_type)), Normalized(_normalized)
        {}

        uint32_t BufferElement::get_component_count() const
        {
            switch (Type)
            {
                case exw::graphics::ShaderDataType::Bool:       return 1U;
                case exw::graphics::ShaderDataType::Int:        return 1U;
                case exw::graphics::ShaderDataType::Int2:       return 2U;
                case exw::graphics::ShaderDataType::Int3:       return 3U;
                case exw::graphics::ShaderDataType::Int4:       return 4U;
                case exw::graphics::ShaderDataType::Float:      return 1U;
                case exw::graphics::ShaderDataType::Float2:     return 2U;
                case exw::graphics::ShaderDataType::Float3:     return 3U;
                case exw::graphics::ShaderDataType::Float4:     return 4U;
                case exw::graphics::ShaderDataType::Matrix3:    return 3U;
                case exw::graphics::ShaderDataType::Matrix4:    return 4U;
            }

            EXW_ASSERT_CORE(false, "ShaderDataType {0} is not supported.", (uint32_t)Type);
            return 0U;
        }

        BufferLayout::BufferLayout(std::initializer_list<BufferElement> _elements)
            : m_Elements(_elements)
        {
            calculate_offset_and_stride();
        }

        void BufferLayout::calculate_offset_and_stride()
        {
            size_t offset = 0Ui64;
            m_Stride = 0U;

            for (auto& element : m_Elements)
            {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
        }

    }
}
#pragma endregion
