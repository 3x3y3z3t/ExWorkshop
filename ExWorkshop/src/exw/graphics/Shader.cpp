// ;
#include "expch.h"
#include "exw\graphics\Shader.h"

#include "exw\graphics\RenderAPI.h"

#include "platform\OpenGL\OpenGLShader.h"

namespace exw
{
    namespace graphics
    {
        refs::ref<Shader> Shader::create(const std::string& _filepath)
        {
            switch (RenderAPI::get())
            {
                case RenderAPI::API::None:      EXW_ASSERT(false, "RenderAPI::None is not supported."); return nullptr;
                case RenderAPI::API::OpenGL:    return refs::create_scoped<OpenGLShader>(_filepath);
                case RenderAPI::API::DirectX:   EXW_ASSERT(false, "RenderAPI::DirectX is not supported."); return nullptr;
                case RenderAPI::API::Vulkan:    EXW_ASSERT(false, "RenderAPI::Vulkan is not supported."); return nullptr;
            }

            EXW_ASSERT(false, "Unknown RenderAPI is not supported.");
            return nullptr;
        }

        refs::ref<Shader> Shader::create(const std::string& _shaderName, const std::string& _vertSrc, const std::string& _fragSrc)
        {
            switch (RenderAPI::get())
            {
                case RenderAPI::API::None:      EXW_ASSERT(false, "RenderAPI::None is not supported."); return nullptr;
                case RenderAPI::API::OpenGL:    return refs::create_scoped<OpenGLShader>(_shaderName, _vertSrc, _fragSrc);
                case RenderAPI::API::DirectX:   EXW_ASSERT(false, "RenderAPI::DirectX is not supported."); return nullptr;
                case RenderAPI::API::Vulkan:    EXW_ASSERT(false, "RenderAPI::Vulkan is not supported."); return nullptr;
            }

            EXW_ASSERT(false, "Unknown RenderAPI is not supported.");
            return nullptr;
        }

        void ShaderManager::add(const refs::ref<Shader>& _shader)
        {
            auto& name = _shader->get_name();
            add(name, _shader);
        }

        void ShaderManager::add(const std::string& _shaderName, const refs::ref<Shader>& _shader)
        {
            EXW_ASSERT(!is_exist(_shaderName), "This shader has already been added.");
            m_Shaders[_shaderName] = _shader;
        }

        refs::ref<Shader> ShaderManager::load(const std::string& _filepath)
        {
            auto shader = Shader::create(_filepath);
            add(shader);
            return shader;
        }

        refs::ref<Shader> ShaderManager::load(const std::string& _shaderName, const std::string& _filepath)
        {
            auto shader = Shader::create(_filepath);
            add(_shaderName, shader);
            return shader;
        }

        bool ShaderManager::is_exist(const std::string& _shaderName) const
        {
            return m_Shaders.find(_shaderName) != m_Shaders.end();
        }

        refs::ref<Shader> ShaderManager::get(const std::string& _shaderName)
        {
            EXW_ASSERT(is_exist(_shaderName), "Shader not found.");
            return m_Shaders[_shaderName];
        }
    }
}
