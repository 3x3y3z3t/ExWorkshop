// ;
#pragma once

#include "exw\graphics\Shader.h"

#include "exw\maths\vector2.h"
#include "exw\maths\vector3.h"
#include "exw\maths\vector4.h"
#include "exw\maths\matrix4.h"

#include <glad\glad.h>

namespace exw
{
    namespace graphics
    {
        class OpenGLShader : public Shader
        {
        public:
            OpenGLShader(const std::string& _filepath);
            OpenGLShader(const std::string& _shaderName, const std::string& _vertSrc, const std::string& _fragSrc);
            virtual ~OpenGLShader();

        public:
            virtual void bind() const override;
            virtual void unbind() const override;

            virtual const std::string& get_name() const override { return m_Name; }

            virtual void set_uniform_int(const std::string& _name, int _value) override;
            virtual void set_uniform_int_arr(const std::string& _name, int* _value, uint32_t _count) override;
            virtual void set_uniform_float(const std::string& _name, float _value) override;
            virtual void set_uniform_float2(const std::string& _name, const maths::vector2& _value) override;
            virtual void set_uniform_float3(const std::string& _name, const maths::vector3& _value) override;
            virtual void set_uniform_float4(const std::string& _name, const maths::vector4& _value) override;
            virtual void set_uniform_mat4x4(const std::string& _name, const maths::matrix4& _value) override;

        private:
            void upload_uniform(const std::string& _name, int _value);
            void upload_uniform(const std::string& _name, int* _value, uint32_t _count);
            void upload_uniform(const std::string& _name, float _value);
            void upload_uniform(const std::string& _name, const maths::vector2& _value);
            void upload_uniform(const std::string& _name, const maths::vector3& _value);
            void upload_uniform(const std::string& _name, const maths::vector4& _value);
            //void upload_uniform(const std::string& _name, const maths::matrix3& _value);
            void upload_uniform(const std::string& _name, const maths::matrix4& _value);

            std::string read_source_from_file(const std::string& _filepath);
            std::unordered_map<GLenum, std::string> pre_process_source(const std::string& _source);
            bool compile(const std::unordered_map<GLenum, std::string>& _shaderSources);

        private:
            uint32_t m_Renderer_id;
            std::string m_Name;
        };
    }
}
