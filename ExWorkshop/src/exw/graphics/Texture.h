/*  Texture.h
*   Version: 1.0 (2022.08.27)
*
*   Contributor
*       Arime-chan
*/
#pragma once

#include "exwpch.h"
#include "exw\Common.h"

namespace exw
{
    namespace graphics
    {
        class Texture
        {
        public:
            virtual ~Texture() = default;

            virtual void bind(uint32_t _slot = 0) const = 0;

            virtual bool is_loaded() const = 0;
            virtual uint32_t get_width() const = 0;
            virtual uint32_t get_height() const = 0;
            virtual uint32_t get_renderer_id() const = 0;

            virtual const std::string& get_filepath() const = 0;

            virtual void set_data(void* _data, uint32_t _size) = 0;

            virtual bool operator==(const Texture& _other) const = 0;
        };

        class Texture2D : public Texture
        {
        public:
            static refs::Ref<Texture2D> create(uint32_t _width, uint32_t _height);
            static refs::Ref<Texture2D> create(const std::string& _filepath);
        };

    }
}
