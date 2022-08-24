/*  Shader.cpp
*   Version: 1.1 (2022.08.24)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "exw\Common.h"
#include "exw\utils\Logger.h"
#include "platform\OpenGL\OpenGLShaderLegacy.h"

namespace exw
{
    namespace graphics
    {
        refs::Ref<Shader> Shader::create(const std::string& _filepath)
        {
            RendererAPI::API activeApi = Renderer::get_active_api();
            switch (activeApi)
            {
                case RendererAPI::API::OpenGL:      return refs::create_ref<OpenGLShaderLegacy>(_filepath);
            }

            EXW_LOG_CORE_CRITICAL("RendererAPI {0} is not supported.", (uint8_t)activeApi);
            EXW_ASSERT_CORE(false);
            return nullptr;
        }

        refs::Ref<Shader> Shader::create(const std::string& _name, const std::string& _vertexSource, const std::string& _fragmentSource)
        {
            RendererAPI::API activeApi = Renderer::get_active_api();
            switch (activeApi)
            {
                case RendererAPI::API::OpenGL:      return refs::create_ref<OpenGLShaderLegacy>(_name, _vertexSource, _fragmentSource);
            }

            EXW_LOG_CORE_CRITICAL("RendererAPI {0} is not supported.", (uint8_t)activeApi);
            EXW_ASSERT_CORE(false);
            return nullptr;
        }

        void ShaderFactory::add(const std::string _name, const refs::Ref<Shader>& _shader)
        {
            if (is_existed(_name))
            {
                EXW_LOG_CORE_ERROR("Shader {0} is already existed.", _name);
                return;
            }
            
            m_Shaders[_name] = _shader;
        }

        void ShaderFactory::add(const refs::Ref<Shader>&_shader)
        {
            auto& name = _shader->get_name();
            add(name, _shader);
        }

        refs::Ref<Shader> ShaderFactory::load(const std::string& _filepath)
        {
            auto shader = Shader::create(_filepath);
            add(shader);
            return shader;
        }

        refs::Ref<Shader> ShaderFactory::load(const std::string& _name, const std::string& _filepath)
        {
            auto shader = Shader::create(_filepath);
            add(_name, shader);
            return shader;
        }

        bool ShaderFactory::is_existed(const std::string& _name) const
        {
            return m_Shaders.find(_name) != m_Shaders.end();
        }

        refs::Ref<Shader> ShaderFactory::get(const std::string& _name)
        {
            if (!is_existed(_name))
            {
                EXW_LOG_CORE_ERROR("Shader {0} not found.", _name);
                return nullptr;
            }

            return m_Shaders[_name];
        }

    }
}
