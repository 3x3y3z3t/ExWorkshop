/*  OpenGLShaderLegacy.cpp
*   Version: 1.1 (2022.08.24)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "OpenGLShaderLegacy.h"

#include "exw\Utils\Logger.h"

#include <glad\gl.h>

namespace exw
{
    namespace utils
    {
        GLenum shader_type_from_string(const std::string& _type)
        {
            if (_type == "vertex")
                return GL_VERTEX_SHADER;
            if (_type == "fragment" || _type == "pixel")
                return GL_FRAGMENT_SHADER;


            EXW_LOG_CORE_ERROR("Shader type {0} is not supported.", _type);
            EXW_ASSERT_CORE(false);
            return 0;
        }
    }

    namespace graphics
    {
        OpenGLShaderLegacy::OpenGLShaderLegacy(const std::string& _filepath)
            : m_Filepath(_filepath)
        {
            std::string source = read_file(_filepath);
            auto shaderSources = pre_process(source);
            compile(shaderSources);

            // extract shader name from filepath;
            {
                size_t lastSlash = _filepath.find_last_of("/\\");
                if (lastSlash == std::string::npos)
                    lastSlash = 0;
                else
                    lastSlash += 1;

                size_t lastDot = _filepath.rfind('.');
                size_t offs = 0;
                if (lastDot == std::string::npos)
                    offs = _filepath.size() - lastSlash;
                else
                    offs = lastDot - lastSlash;

                m_Name = _filepath.substr(lastSlash, offs);
            }
        }

        OpenGLShaderLegacy::OpenGLShaderLegacy(const std::string& _name, const std::string& _vertexSource, const std::string& _fragmentSource)
            : m_Name(_name)
        {
            std::unordered_map<GLenum, std::string> sources;
            sources[GL_VERTEX_SHADER] = _vertexSource;
            sources[GL_FRAGMENT_SHADER] = _fragmentSource;

            compile(sources);
        }

        OpenGLShaderLegacy::~OpenGLShaderLegacy()
        {
            glDeleteProgram(m_Renderer_id);
        }

        void OpenGLShaderLegacy::bind() const
        {
            glUseProgram(m_Renderer_id);
        }

        void OpenGLShaderLegacy::unbind() const
        {
            glUseProgram(0);
        }

        void OpenGLShaderLegacy::set_int(const std::string& _name, int _value)
        {
            GLint location = glGetUniformLocation(m_Renderer_id, _name.c_str());
            glUniform1i(location, _value);
        }

        void OpenGLShaderLegacy::set_int_arr(const std::string& _name, int* _values, uint32_t _count)
        {
            GLint location = glGetUniformLocation(m_Renderer_id, _name.c_str());
            glUniform1iv(location, _count, _values);
        }

        void OpenGLShaderLegacy::set_float(const std::string& _name, float _value)
        {
            GLint location = glGetUniformLocation(m_Renderer_id, _name.c_str());
            glUniform1f(location, _value);
        }

        void OpenGLShaderLegacy::set_float2(const std::string& _name, const maths::vector2& _value)
        {
            GLint location = glGetUniformLocation(m_Renderer_id, _name.c_str());
            glUniform2f(location, _value.x, _value.y);
        }

        void OpenGLShaderLegacy::set_float3(const std::string& _name, const maths::vector3& _value)
        {
            GLint location = glGetUniformLocation(m_Renderer_id, _name.c_str());
            glUniform3f(location, _value.x, _value.y, _value.z);
        }

        void OpenGLShaderLegacy::set_float4(const std::string& _name, const maths::vector4& _value)
        {
            GLint location = glGetUniformLocation(m_Renderer_id, _name.c_str());
            glUniform4f(location, _value.x, _value.y, _value.z, _value.w);
        }

        void OpenGLShaderLegacy::set_matrix4(const std::string& _name, const maths::matrix4& _value)
        {
            GLint location = glGetUniformLocation(m_Renderer_id, _name.c_str());
            glUniformMatrix4fv(location, 1, GL_FALSE, &(_value[0].x));
        }

        std::string OpenGLShaderLegacy::read_file(const std::string& _filepath)
        {
            std::string content;
            std::ifstream stream(_filepath, std::ios::in | std::ios::binary);
            if (stream)
            {
                stream.seekg(0, std::ios::end);
                size_t size = stream.tellg();
                if (size != -1)
                {
                    content.resize(size);
                    stream.seekg(0, std::ios::beg);
                    stream.read(&content[0], size);
                }
                else
                {
                    EXW_LOG_CORE_ERROR("Could not read from file {0}.", _filepath);
                }
            }
            else
            {
                EXW_LOG_CORE_ERROR("Could not open file {0}.", _filepath);
            }

            return content;
        }

        std::unordered_map<uint32_t, std::string> OpenGLShaderLegacy::pre_process(const std::string& _source)
        {
            std::unordered_map<uint32_t, std::string> shaderSources;
            const char* typeToken = "#type";
            size_t typeTokenLength = strlen(typeToken);
            size_t pos = _source.find(typeToken, 0);

            while (pos != std::string::npos)
            {
                size_t eol = _source.find_first_of("\r\n", pos);
                EXW_ASSERT_CORE(eol != std::string::npos, "Syntax error (shader source).");

                size_t begin = pos + typeTokenLength + 1;
                std::string type = _source.substr(begin, eol - begin);
                if (utils::shader_type_from_string(type) == 0U)
                {
                    EXW_LOG_CORE_ERROR("Invalid shader type specifier {0}.", type);
                    EXW_ASSERT_CORE(false);
                }

                size_t nextLinePos = _source.find_first_not_of("\r\n", eol);
                EXW_ASSERT_CORE(nextLinePos != std::string::npos, "Syntax error (shader source).");
                pos = _source.find(typeToken, nextLinePos);

                if (pos == std::string::npos)
                    shaderSources[utils::shader_type_from_string(type)] = _source.substr(nextLinePos);
                else
                    shaderSources[utils::shader_type_from_string(type)] = _source.substr(nextLinePos, pos - nextLinePos);
            }

            return shaderSources;
        }

        void OpenGLShaderLegacy::compile(const std::unordered_map<uint32_t, std::string>& _shaderSources)
        {
            GLuint program = glCreateProgram();
            EXW_ASSERT_CORE(_shaderSources.size() <= 2, "We only support 2 shaders for now");
            std::array<GLenum, 2> glShaderIDs;
            int glShaderIDIndex = 0;
            for (auto& kv : _shaderSources)
            {
                GLenum type = kv.first;
                const std::string& source = kv.second;

                GLuint shader = glCreateShader(type);

                const GLchar* sourceCStr = source.c_str();
                glShaderSource(shader, 1, &sourceCStr, 0);

                glCompileShader(shader);

                GLint isCompiled = 0;
                glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
                if (isCompiled == GL_FALSE)
                {
                    GLint maxLength = 0;
                    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                    std::vector<GLchar> infoLog(maxLength);
                    glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                    glDeleteShader(shader);

                    EXW_LOG_CORE_ERROR("{0}", infoLog.data());
                    EXW_ASSERT_CORE(false, "Shader compilation failure!");
                    break;
                }

                glAttachShader(program, shader);
                glShaderIDs[glShaderIDIndex++] = shader;
            }

            m_Renderer_id = program;

            // Link our program
            glLinkProgram(program);

            // Note the different functions here: glGetProgram* instead of glGetShader*.
            GLint isLinked = 0;
            glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
            if (isLinked == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> infoLog(maxLength);
                glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

                // We don't need the program anymore.
                glDeleteProgram(program);

                for (auto id : glShaderIDs)
                    glDeleteShader(id);

                EXW_LOG_CORE_ERROR("{0}", infoLog.data());
                EXW_ASSERT_CORE(false, "Shader link failure!");
                return;
            }

            for (auto id : glShaderIDs)
                glDetachShader(program, id);
        }

    }
}
