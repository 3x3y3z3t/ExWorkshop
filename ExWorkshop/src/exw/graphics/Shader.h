// ;
#pragma once

#include "exw\Common.h"

#include "exw\maths\vector2.h"
#include "exw\maths\vector3.h"
#include "exw\maths\vector4.h"
#include "exw\maths\matrix4.h"

namespace exw
{
    namespace graphics
    {
        class Shader
        {
        public:
            virtual ~Shader() = default;

        public:
            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual const std::string& get_name() const = 0;

            virtual void set_uniform_int(const std::string& _name, int _value) = 0;
            virtual void set_uniform_int_arr(const std::string& _name, int* _value, uint32_t _count) = 0;
            virtual void set_uniform_float(const std::string& _name, float _value) = 0;
            virtual void set_uniform_float2(const std::string& _name, const maths::vector2& _value) = 0;
            virtual void set_uniform_float3(const std::string& _name, const maths::vector3& _value) = 0;
            virtual void set_uniform_float4(const std::string& _name, const maths::vector4& _value) = 0;
            virtual void set_uniform_mat4x4(const std::string& _name, const maths::matrix4& _value) = 0;

            static refs::ref<Shader> create(const std::string& _filepath);
            static refs::ref<Shader> create(const std::string& _shaderName, const std::string& _vertSrc, const std::string& _fragSrc);
        };

        class ShaderManager
        {
        public:
            void add(const refs::ref<Shader>& _shader);
            void add(const std::string& _shaderName, const refs::ref<Shader>& _shader);

            refs::ref<Shader> load(const std::string& _filepath);
            refs::ref<Shader> load(const std::string& _shaderName, const std::string& _filepath);

            bool is_exist(const std::string& _shaderName) const;
            refs::ref<Shader> get(const std::string& _shaderName);

        private:
            std::unordered_map<std::string, refs::ref<Shader>> m_Shaders;
        };
    }
}
