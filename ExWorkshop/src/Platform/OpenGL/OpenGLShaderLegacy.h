/*  OpenGLShaderLegacy.h
*   Version: 1.0 (2022.08.24)
*
*   Contributor
*       Arime-chan
*/
#pragma once

#include "exw\graphics\Shader.h"
#include "exw\maths\Maths.h"

namespace exw
{
    namespace graphics
    {
        class OpenGLShaderLegacy : public Shader
        {
        public:
            OpenGLShaderLegacy(const std::string& _filepath);
            OpenGLShaderLegacy(const std::string& _name, const std::string& _vertexSource, const std::string& _fragmentSource);
            virtual ~OpenGLShaderLegacy();

            virtual void bind() const override;
            virtual void unbind() const override;

            virtual void set_int(const std::string& _name, int _value) override;
            virtual void set_int_arr(const std::string& _name, int* _values, uint32_t _count) override;
            virtual void set_float(const std::string& _name, float _value) override;
            virtual void set_float2(const std::string& _name, const maths::vector2& _value) override;
            virtual void set_float3(const std::string& _name, const maths::vector3& _value) override;
            virtual void set_float4(const std::string& _name, const maths::vector4& _value) override;
            virtual void set_matrix4(const std::string& _name, const maths::matrix4& _value) override;

            virtual const std::string& get_name() const override { return m_Name; }

        private:
            std::string read_file(const std::string& _filepath);
            std::unordered_map<uint32_t, std::string> pre_process(const std::string& _source);
            void compile(const std::unordered_map<uint32_t, std::string>& _shaderSources);

        private:
            uint32_t m_Renderer_id = 0;
            std::string m_Filepath;
            std::string m_Name;


        };

    }
}
