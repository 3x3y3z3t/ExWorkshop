// ;
#include "expch.h"
#include "Renderer2D.h"

#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Buffers.h"

#include "exw\maths\math_utils.h"
#include "exw\maths\vector2.h"
#include "exw\maths\vector3.h"
#include "exw\maths\vector4.h"
#include "exw\maths\matrix4.h"

#include <glm\gtx\transform.hpp>

namespace exw
{
    namespace graphics
    {
        struct QuadVertex
        {
            maths::vector3 position = { 0.0f };
            maths::vector4 color = { 0.0f };
            maths::vector2 texcoord = { 0.0f };
            float texid = 0.0f;
            float tilingfactor = 0.0f;
        };

        /* 2D renderer internal storage. */
        struct Renderer2DData
        {
            static constexpr uint32_t MaxQuads = 10'000U;
            static constexpr uint32_t MaxQuadVertices = MaxQuads * 4U;
            static constexpr uint32_t MaxQuadIndices = MaxQuads * 6U;
            static constexpr uint32_t MaxTextureSlots = 32U;

            refs::ref<VertexArray> QuadVertexArray;
            refs::ref<VertexBuffer> QuadVertexBuffer;
            refs::ref<Shader> TextureShader;
            refs::ref<Texture2D> WhiteTexture;

            uint32_t QuadIndexCount = 0U;
            QuadVertex* QuadVertexBufferHead = nullptr;
            QuadVertex* QuadVertexBufferPtr = nullptr;

            std::array<refs::ref<Texture2D>, MaxTextureSlots> TextureSlots;
            uint32_t TextureSlotIndex = 1U;

            exw::maths::vector4 QuadVertexPos[4];

            maths::matrix4 ViewProjectionMatrix;
            uint32_t Width = 1280U;
            uint32_t Height = 720U;

            Renderer2D::RendererStatistics Stats;
        };
        static Renderer2DData s_Data;

        void Renderer2D::init()
        {
            EXW_PROFILE_FUNCTION();
            // init quads;
            {
                s_Data.QuadVertexBufferHead = new QuadVertex[s_Data.MaxQuadVertices];
                s_Data.QuadVertexArray = VertexArray::create();

                s_Data.QuadVertexBuffer = VertexBuffer::create(s_Data.MaxQuadVertices * sizeof(QuadVertex));
                s_Data.QuadVertexBuffer->set_layout({
                    { ShaderDataType::Float3, "i_Position" },
                    { ShaderDataType::Float4, "i_Color" },
                    { ShaderDataType::Float2, "i_Texcoord" },
                    { ShaderDataType::Float, "i_Texid" },
                    { ShaderDataType::Float, "i_Tilingfactor" },
                });
                s_Data.QuadVertexArray->add_vertex_buffer(s_Data.QuadVertexBuffer);

                uint32_t* quadIndices = new uint32_t[s_Data.MaxQuadIndices];
                uint32_t offs = 0U;
                for (uint32_t i = 0U; i < s_Data.MaxQuadIndices; i += 6U)
                {
                    quadIndices[i + 0U] = offs + 0U;
                    quadIndices[i + 1U] = offs + 1U;
                    quadIndices[i + 2U] = offs + 2U;
                    quadIndices[i + 3U] = offs + 2U;
                    quadIndices[i + 4U] = offs + 3U;
                    quadIndices[i + 5U] = offs + 0U;
                    offs += 4U;
                }

                refs::ref<IndexBuffer> quadIndexBuffer = IndexBuffer::create(quadIndices, s_Data.MaxQuadIndices);
                s_Data.QuadVertexArray->set_index_buffer(quadIndexBuffer);
                delete[] quadIndices;

                int samplers[s_Data.MaxTextureSlots];
                for (uint32_t i = 0U; i < s_Data.MaxTextureSlots; ++i)
                {
                    samplers[i] = i;
                }

                s_Data.WhiteTexture = Texture2D::create(1, 1);
                uint32_t data = 0xffffffffU;
                //uint32_t data = 0x00000000U;
                s_Data.WhiteTexture->set_data(&data, sizeof(uint32_t));

                s_Data.TextureShader = Shader::create("res/shaders/texture.glsl");
                s_Data.TextureShader->bind();
                s_Data.TextureShader->set_uniform_int_arr("u_Textures", samplers, s_Data.MaxTextureSlots);
                s_Data.TextureSlots[0] = s_Data.WhiteTexture;

                s_Data.QuadVertexPos[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
                s_Data.QuadVertexPos[1] = { +0.5f, -0.5f, 0.0f, 1.0f };
                s_Data.QuadVertexPos[2] = { +0.5f, +0.5f, 0.0f, 1.0f };
                s_Data.QuadVertexPos[3] = { -0.5f, +0.5f, 0.0f, 1.0f };
            }
        }

        void Renderer2D::shutdown()
        {
            EXW_PROFILE_FUNCTION();
            delete[] s_Data.QuadVertexBufferHead;
        }

        //void Renderer2D::set_viewport(uint _width, uint _height)
        //{
        //    s_Data.Width = _width;
        //    s_Data.Height = _height;
        //}

        void Renderer2D::begin_scene(const Camera& _camera, const maths::matrix4& _transform)
        {
            EXW_PROFILE_FUNCTION();
            maths::matrix4 viewProj = _camera.get_projection() * maths::matrix4::inverse(_transform);

            s_Data.TextureShader->bind();
            s_Data.TextureShader->set_uniform_mat4x4("u_ViewProjMat", viewProj);

            start_batch();
        }

        void Renderer2D::begin_scene(const OrthographicCamera& _camera)
        {
            EXW_PROFILE_FUNCTION();
            s_Data.TextureShader->bind();
            s_Data.TextureShader->set_uniform_mat4x4("u_ViewProjMat", _camera.get_view_proj_matrix());

            start_batch();
        }

        void Renderer2D::end_scene()
        {
            EXW_PROFILE_FUNCTION();
            flush();
        }

        void Renderer2D::flush()
        {
            if (s_Data.QuadIndexCount == 0U)
            {
                return;
            }

            uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferHead);
            s_Data.QuadVertexBuffer->set_data(s_Data.QuadVertexBufferHead, dataSize);

            for (uint32_t i = 0U; i < s_Data.TextureSlotIndex; ++i)
            {
                s_Data.TextureSlots[i]->bind(i);
            }

            RenderCommand::draw_indexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
            ++s_Data.Stats.DrawCalls;
        }

        void Renderer2D::reset_stats()
        {
            memset(&s_Data.Stats, 0, sizeof(Renderer2D::RendererStatistics));
        }

        const Renderer2D::RendererStatistics& Renderer2D::get_stats()
        {
            return s_Data.Stats;
        }

        void Renderer2D::draw_quad(const maths::vector2& _position, const maths::vector2& _size, const maths::vector4& _color)
        {
            draw_quad({ _position.x, _position.y, 0.0f }, _size, 0.0f, _color);
        }

        void Renderer2D::draw_quad(const maths::vector3& _position, const maths::vector2& _size, const maths::vector4& _color)
        {
            draw_quad(_position, _size, 0.0f, _color);
        }

        void Renderer2D::draw_quad(const maths::vector2& _position, const maths::vector2& _size, float _rotation, const maths::vector4& _color)
        {
            draw_quad({ _position.x, _position.y, 0.0f }, _size, _rotation, _color);
        }

        void Renderer2D::draw_quad(const maths::vector3& _position, const maths::vector2& _size, float _rotation, const maths::vector4& _color)
        {
            EXW_PROFILE_FUNCTION();
            maths::matrix4 transform;
            if (_rotation == 0.0f)
            {
                transform = exw::maths::translate(exw::maths::matrix4(1.0f), _position)
                    * exw::maths::scale(exw::maths::matrix4(1.0f), { _size.x, _size.y, 1.0f });
            }
            else
            {
                transform = exw::maths::translate(exw::maths::matrix4(1.0f), _position)
                    * exw::maths::rotate(exw::maths::matrix4(1.0f), exw::maths::to_radians(_rotation), { 0.0f, 0.0f, 1.0f })
                    * exw::maths::scale(exw::maths::matrix4(1.0f), { _size.x, _size.y, 1.0f });
            }

            draw_quad(transform, _color);
        }

        void Renderer2D::draw_quad(const maths::vector2& _position, const maths::vector2& _size, const refs::ref<Texture2D>& _texture, float _tilingFactor, const maths::vector4& _tintColor)
        {
            draw_quad({ _position.x, _position.y, 0.0f }, _size, 0.0f, _texture, _tilingFactor, _tintColor);
        }

        void Renderer2D::draw_quad(const maths::vector3& _position, const maths::vector2& _size, const refs::ref<Texture2D>& _texture, float _tilingFactor, const maths::vector4& _tintColor)
        {
            draw_quad(_position, _size, 0.0f, _texture, _tilingFactor, _tintColor);
        }

        void Renderer2D::draw_quad(const maths::vector2& _position, const maths::vector2& _size, float _rotation, const refs::ref<Texture2D>& _texture, float _tilingFactor, const maths::vector4& _tintColor)
        {
            draw_quad({ _position.x, _position.y, 0.0f }, _size, _rotation, _texture, _tilingFactor, _tintColor);
        }

        void Renderer2D::draw_quad(const maths::vector3& _position, const maths::vector2& _size, float _rotation, const refs::ref<Texture2D>& _texture, float _tilingFactor, const maths::vector4& _tintColor)
        {
            EXW_PROFILE_FUNCTION();
            maths::matrix4 transform;
            if (_rotation == 0.0f)
            {
                transform = exw::maths::translate(exw::maths::matrix4(1.0f), _position)
                    * exw::maths::scale(exw::maths::matrix4(1.0f), { _size.x, _size.y, 1.0f });
            }
            else
            {
                transform = exw::maths::translate(exw::maths::matrix4(1.0f), _position)
                    * exw::maths::rotate(exw::maths::matrix4(1.0f), exw::maths::to_radians(_rotation), { 0.0f, 0.0f, 1.0f })
                    * exw::maths::scale(exw::maths::matrix4(1.0f), { _size.x, _size.y, 1.0f });
            }

            draw_quad(transform, _texture, _tilingFactor, _tintColor);
        }

        void Renderer2D::draw_quad(const maths::matrix4& _transform, const maths::vector4& _color)
        {
            EXW_PROFILE_FUNCTION();
            if (s_Data.QuadIndexCount >= Renderer2DData::MaxQuadIndices)
            {
                next_batch();
            }

            constexpr size_t quadVertexCount = 4;
            constexpr float texId = 0.0f;
            const maths::vector2 texCoords[4] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
            constexpr float tilingFactor = 1.0f;

            for (size_t i = 0U; i < quadVertexCount; ++i)
            {
                auto& pos = _transform * s_Data.QuadVertexPos[i];
                s_Data.QuadVertexBufferPtr->position = { pos.x, pos.y, pos.z };
                s_Data.QuadVertexBufferPtr->color = _color;
                s_Data.QuadVertexBufferPtr->texcoord = texCoords[i];
                s_Data.QuadVertexBufferPtr->texid = texId;
                s_Data.QuadVertexBufferPtr->tilingfactor = tilingFactor;
                ++s_Data.QuadVertexBufferPtr;
            }

            s_Data.QuadIndexCount += 6U;
            ++s_Data.Stats.QuadCount;
        }

        void Renderer2D::draw_quad(const maths::matrix4& _transform, const refs::ref<Texture2D>& _texture, float _tilingFactor, const maths::vector4& _tintColor)
        {
            EXW_PROFILE_FUNCTION();
            if (s_Data.QuadIndexCount >= Renderer2DData::MaxQuadIndices)
            {
                next_batch();
            }

            constexpr size_t quadVertexCount = 4;
            float texId = 0.0f;
            const maths::vector2 texCoords[4] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

            for (uint32_t i = 1; i < s_Data.TextureSlotIndex; ++i)
            {
                if (*s_Data.TextureSlots[i] == *_texture)
                {
                    texId = (float)i;
                    break;
                }
            }
            if (texId == 0.0f)
            {
                if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
                {
                    next_batch();
                }

                texId = (float)s_Data.TextureSlotIndex;
                s_Data.TextureSlots[s_Data.TextureSlotIndex] = _texture;
                ++s_Data.TextureSlotIndex;
            }

            for (size_t i = 0U; i < quadVertexCount; ++i)
            {
                auto& pos = _transform * s_Data.QuadVertexPos[i];
                s_Data.QuadVertexBufferPtr->position = { pos.x, pos.y, pos.z };
                s_Data.QuadVertexBufferPtr->color = _tintColor;
                s_Data.QuadVertexBufferPtr->texcoord = texCoords[i];
                s_Data.QuadVertexBufferPtr->texid = texId;
                s_Data.QuadVertexBufferPtr->tilingfactor = _tilingFactor;
                ++s_Data.QuadVertexBufferPtr;
            }

            s_Data.QuadIndexCount += 6U;
            ++s_Data.Stats.QuadCount;
        }

        void Renderer2D::start_batch()
        {
            s_Data.QuadIndexCount = 0U;
            s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferHead;
            s_Data.TextureSlotIndex = 1U;
        }

        void Renderer2D::next_batch()
        {
            flush();
            start_batch();
        }
    }
}
