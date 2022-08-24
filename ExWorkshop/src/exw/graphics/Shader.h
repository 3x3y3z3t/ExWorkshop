/*  Shader.h
*   Version: 1.0 (2022.07.23)
*
*   Contributor
*       Arime-chan
*/
#pragma once
#include "exwpch.h"

#include "exw\Common.h"
#include "exw\maths\Maths.h"

namespace exw
{
    namespace graphics
    {
        class Shader
        {
        public:
            virtual ~Shader() = default;

            static refs::Ref<Shader> create(const std::string& _filepath);
            static refs::Ref<Shader> create(const std::string& _name, const std::string& _vertexSource, const std::string& _fragmentSource);

            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual void set_int(const std::string& _name, int _value) = 0;
            virtual void set_int_arr(const std::string& _name, int* _values, uint32_t _count) = 0;
            virtual void set_float(const std::string& _name, float _value) = 0;
            virtual void set_float2(const std::string& _name, const maths::vector2& _value) = 0;
            virtual void set_float3(const std::string& _name, const maths::vector3& _value) = 0;
            virtual void set_float4(const std::string& _name, const maths::vector4& _value) = 0;
            virtual void set_matrix4(const std::string& _name, const maths::matrix4& _value) = 0;

            virtual const std::string& get_name() const = 0;
        };

        class ShaderFactory
        {
        public:
            void add(const std::string _name, const refs::Ref<Shader>& _shader);
            void add(const refs::Ref<Shader>& _shader);

            refs::Ref<Shader>load(const std::string& _filepath);
            refs::Ref<Shader>load(const std::string& _name, const std::string& _filepath);

            bool is_existed(const std::string& _name) const;
            refs::Ref<Shader> get(const std::string& _name);

        private:
            std::unordered_map<std::string, refs::Ref<Shader>> m_Shaders;
        };

    }
}
