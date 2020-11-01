// ;
#pragma once

#include "exw\Common.h"

#include "exw\graphics\Textures.h"
#include "exw\graphics\camera\Camera.h"
#include "exw\graphics\camera\OrthographicCamera.h"

#include "exw\maths\vector2.h"
#include "exw\maths\vector3.h"
#include "exw\maths\vector4.h"
#include "exw\maths\matrix4.h"

namespace exw
{
    namespace graphics
    {
        class Renderer2D
        {
        public:
            struct RendererStatistics
            {
                uint32_t DrawCalls = 0U;
                uint32_t QuadCount = 0U;

                uint32_t get_vertex_count() const { return QuadCount * 4U; }
                uint32_t get_index_count() const { return QuadCount * 6U; }
            };

            static constexpr float s_Min_width = 0.003f;

        public:
            static void init();
            static void shutdown();
            //static void set_viewport(uint32_t _width, uint32_t _height);

            static void begin_scene(const Camera& _camera, const maths::matrix4& _transform);
            __declspec(deprecated) static void begin_scene(const OrthographicCamera& _camera);
            static void end_scene();
            static void flush();

            static void reset_stats();
            static const RendererStatistics& get_stats();

            static void draw_quad(const maths::vector2& _position, const maths::vector2& _size, const maths::vector4& _color);
            static void draw_quad(const maths::vector3& _position, const maths::vector2& _size, const maths::vector4& _color);
            static void draw_quad(const maths::vector2& _position, const maths::vector2& _size, float _rotation, const maths::vector4& _color);
            static void draw_quad(const maths::vector3& _position, const maths::vector2& _size, float _rotation, const maths::vector4& _color);

            static void draw_quad(const maths::vector2& _position, const maths::vector2& _size, const refs::ref<Texture2D>& _texture, float _tilingFactor = 1.0f, const maths::vector4& _tintColor = { 1.0f });
            static void draw_quad(const maths::vector3& _position, const maths::vector2& _size, const refs::ref<Texture2D>& _texture, float _tilingFactor = 1.0f, const maths::vector4& _tintColor = { 1.0f });
            static void draw_quad(const maths::vector2& _position, const maths::vector2& _size, float _rotation, const refs::ref<Texture2D>& _texture, float _tilingFactor = 1.0f, const maths::vector4& _tintColor = { 1.0f });
            static void draw_quad(const maths::vector3& _position, const maths::vector2& _size, float _rotation, const refs::ref<Texture2D>& _texture, float _tilingFactor = 1.0f, const maths::vector4& _tintColor = { 1.0f });

            static void draw_quad(const maths::matrix4& _transform, const maths::vector4& _color);
            static void draw_quad(const maths::matrix4& _transform, const refs::ref<Texture2D>& _texture, float _tilingFactor = 1.0f, const maths::vector4& _tintColor = { 1.0f });
        private:
            static void start_batch();
            static void next_batch();
        };
    }
}
