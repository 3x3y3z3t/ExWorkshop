// ;
#pragma once

#include "exw\Common.h"

namespace exw
{
    namespace graphics
    {
        class Texture
        {
        public:
            virtual ~Texture() = default;

        public:
            virtual void bind(uint32_t _slot = 0) const = 0;

            virtual uint32_t get_renderer_id() const = 0;
            virtual uint32_t get_width() const = 0;
            virtual uint32_t get_height() const = 0;

            virtual void set_data(void* _data, uint32_t _size) = 0;

            virtual bool operator==(const Texture& _texture) const = 0;
            bool operator !=(const Texture& _texture) const { return !(*this == _texture); }
        };

        class Texture2D : public Texture
        {
        public:
            static refs::ref<Texture2D> create(uint32_t _width, uint32_t _height);
            static refs::ref<Texture2D> create(const std::string& _filepath);
        };
    }
}
