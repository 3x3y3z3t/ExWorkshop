// ;
#include "expch.h"
#include "OpenGLShader.h"

#include "exw\Common.h"

#include <glad\glad.h>
#include <glm\gtc\type_ptr.hpp>

namespace exw
{
    namespace graphics
    {
        #define get_uniform_location(_id, _name) glGetUniformLocation(_id, _name)

        static GLenum shader_type_from_string(const std::string& _type)
        {
            if (_type == "vertex")
                return GL_VERTEX_SHADER;
            if (_type == "fragment" || _type == "pixel")
                return GL_FRAGMENT_SHADER;

            EXW_ASSERT(false, "Unknown shader type.");
            return 0;
        }

        OpenGLShader::OpenGLShader(const std::string& _filepath)
        {
            EXW_PROFILE_FUNCTION();
            std::string source = read_source_from_file(_filepath);
            auto shaderSources = pre_process_source(source);
            compile(shaderSources);

            auto lastSlash = _filepath.find_last_of("/\\");
            lastSlash = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;

            auto lastDot = _filepath.rfind('.');
            auto count = (lastDot == std::string::npos) ? _filepath.size() - lastSlash : lastDot - lastSlash;
            m_Name = _filepath.substr(lastSlash, count);
        }

        OpenGLShader::OpenGLShader(const std::string& _shaderName, const std::string& _vertSrc, const std::string& _fragSrc)
            : m_Name(_shaderName)
        {
            EXW_PROFILE_FUNCTION();
            std::unordered_map<GLenum, std::string> shaderSources;
            shaderSources[GL_VERTEX_SHADER] = _vertSrc;
            shaderSources[GL_FRAGMENT_SHADER] = _fragSrc;
            compile(shaderSources);
        }

        OpenGLShader::~OpenGLShader()
        {
            EXW_PROFILE_FUNCTION();
            glDeleteProgram(m_Renderer_id);
        }

        void OpenGLShader::bind() const
        {
            EXW_PROFILE_FUNCTION();
            glUseProgram(m_Renderer_id);
        }

        void OpenGLShader::unbind() const
        {
            EXW_PROFILE_FUNCTION();
            glUseProgram(0);
        }

        void OpenGLShader::set_uniform_int(const std::string& _name, int _value)
        {
            EXW_PROFILE_FUNCTION();
            upload_uniform(_name, _value);
        }

        void OpenGLShader::set_uniform_int_arr(const std::string& _name, int* _value, uint32_t _count)
        {
            EXW_PROFILE_FUNCTION();
            upload_uniform(_name, _value, _count);
        }

        void OpenGLShader::set_uniform_float(const std::string& _name, float _value)
        {
            EXW_PROFILE_FUNCTION();
            upload_uniform(_name, _value);
        }

        void OpenGLShader::set_uniform_float2(const std::string& _name, const maths::vector2& _value)
        {
            EXW_PROFILE_FUNCTION();
            upload_uniform(_name, _value);
        }

        void OpenGLShader::set_uniform_float3(const std::string& _name, const maths::vector3& _value)
        {
            EXW_PROFILE_FUNCTION();
            upload_uniform(_name, _value);
        }

        void OpenGLShader::set_uniform_float4(const std::string& _name, const maths::vector4& _value)
        {
            EXW_PROFILE_FUNCTION();
            upload_uniform(_name, _value);
        }

        void OpenGLShader::set_uniform_mat4x4(const std::string& _name, const maths::matrix4& _value)
        {
            EXW_PROFILE_FUNCTION();
            upload_uniform(_name, _value);
        }

        void OpenGLShader::upload_uniform(const std::string& _name, int _value)
        {
            glUniform1i(glGetUniformLocation(m_Renderer_id, _name.c_str()), _value);
        }

        void OpenGLShader::upload_uniform(const std::string& _name, int* _value, uint32_t _count)
        {
            glUniform1iv(glGetUniformLocation(m_Renderer_id, _name.c_str()), _count, _value);
        }

        void OpenGLShader::upload_uniform(const std::string& _name, float _value)
        {
            glUniform1f(glGetUniformLocation(m_Renderer_id, _name.c_str()), _value);
        }

        void OpenGLShader::upload_uniform(const std::string& _name, const maths::vector2& _value)
        {
            glUniform2f(glGetUniformLocation(m_Renderer_id, _name.c_str()), _value.x, _value.y);
        }

        void OpenGLShader::upload_uniform(const std::string& _name, const maths::vector3& _value)
        {
            glUniform3f(glGetUniformLocation(m_Renderer_id, _name.c_str()), _value.x, _value.y, _value.z);
        }

        void OpenGLShader::upload_uniform(const std::string& _name, const maths::vector4& _value)
        {
            glUniform4f(glGetUniformLocation(m_Renderer_id, _name.c_str()), _value.x, _value.y, _value.z, _value.w);
        }

        void OpenGLShader::upload_uniform(const std::string& _name, const maths::matrix4& _value)
        {
            glUniformMatrix4fv(glGetUniformLocation(m_Renderer_id, _name.c_str()), 1, GL_FALSE, &_value.raw[0].x);
        }

        std::string OpenGLShader::read_source_from_file(const std::string& _filepath)
        {
            EXW_PROFILE_FUNCTION();
            std::string res;
            std::ifstream ifs(_filepath, std::ios::in | std::ios::binary);

            if (ifs)
            {
                ifs.seekg(0, std::ios::end);
                size_t size = ifs.tellg();
                if (size != -1)
                {
                    res.resize(size);
                    ifs.seekg(0, std::ios::beg);
                    ifs.read(&res[0], size);
                    //ifs.close(); // ifstream closes itself due to RAII;
                }
                else
                {
                    EXW_LOG_ERROR("File read failure: {1}", _filepath);
                    //EXW_ASSERT(false, "");
                }
            }
            else
            {
                EXW_LOG_ERROR("File open failure: {1}", _filepath);
                //EXW_ASSERT(false, "");
            }

            return res;
        }

        std::unordered_map<uint32_t, std::string> OpenGLShader::pre_process_source(const std::string& _source)
        {
            EXW_PROFILE_FUNCTION();
            std::unordered_map<GLenum, std::string> shaderSources;

            const char* typeToken = "#type";
            size_t typeTokenLength = strlen(typeToken); // TODO: hard-code this;
            size_t pos = _source.find(typeToken, 0);
            while (pos != std::string::npos)
            {
                size_t eol = _source.find_first_of("\r\n", pos);
                EXW_ASSERT(eol != std::string::npos, "syntax error");

                size_t begin = pos + typeTokenLength + 1;
                std::string type = _source.substr(begin, eol - begin);
                EXW_ASSERT(shader_type_from_string(type), "invalid shader type");

                size_t nextLinePos = _source.find_first_not_of("\r\n", eol);
                EXW_ASSERT(nextLinePos != std::string::npos, "syntax error ");
                pos = _source.find(typeToken, nextLinePos);

                shaderSources[shader_type_from_string(type)] = (pos == std::string::npos) ? _source.substr(nextLinePos) : _source.substr(nextLinePos, pos - nextLinePos);
            }

            return shaderSources;
        }

        bool OpenGLShader::compile(const std::unordered_map<uint32_t, std::string>& _shaderSources)
        {
            EXW_PROFILE_FUNCTION();
            // TODO: don't crash the program;
            GLuint program = glCreateProgram();
            EXW_ASSERT(_shaderSources.size() <= 2, "Multiple shaders is not supported.");

            //std::array<GLenum, 2> glShaderIds;
            GLenum shaders[2];
            int index = 0;
            for (auto& item : _shaderSources)
            {
                GLenum type = item.first;
                const GLchar* source = item.second.c_str();

                GLuint shader = glCreateShader(type);
                glShaderSource(shader, 1, &source, 0);
                glCompileShader(shader);
                GLint stat = 0;
                glGetShaderiv(shader, GL_COMPILE_STATUS, &stat);
                if (stat == GL_FALSE)
                {
                    GLint length = 0;
                    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
                    std::vector<GLchar> info(length);
                    glGetShaderInfoLog(shader, length, &length, &info[0]);
                    //glDeleteShader(shader);

                    for (auto sh : shaders)
                        glDeleteShader(sh);

                    EXW_LOG_ERROR("Shader compilation failure: {0}", info.data());
                    EXW_ASSERT(false, "");
                    return false;
                    //break;
                }

                glAttachShader(program, shader);
                shaders[index++] = shader;
            }

            m_Renderer_id = program;

            glLinkProgram(program);
            GLint stat = 0;
            glGetProgramiv(program, GL_LINK_STATUS, (int*)&stat);
            if (stat == GL_FALSE)
            {
                GLint length = 0;
                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
                std::vector<GLchar> info(length);
                glGetProgramInfoLog(program, length, &length, &info[0]);
                glDeleteProgram(program);

                for (auto shader : shaders)
                    glDeleteShader(shader);

                EXW_LOG_ERROR("Shader link failure: {0}", info.data());
                EXW_ASSERT(false, "");
                return false;
            }

            for (auto shader : shaders)
            {
                glDetachShader(program, shader);
                glDeleteShader(shader);
            }

            return true;
        }
    }
}
