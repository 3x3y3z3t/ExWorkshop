/*  OpenGLShader.cpp
*   Version: 1.1 (2022.08.24)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "OpenGLShader.h"

#include "exw\Utils\Logger.h"

#include <glad\gl.h>

#include <shaderc\shaderc.hpp>
#include <spirv_cross\spirv_cross.hpp>
#include <spirv_cross\spirv_glsl.hpp>

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

        static constexpr shaderc_shader_kind gl_shader_stage_to_shaderc(GLenum _stage)
        {
            switch (_stage)
            {
                case GL_VERTEX_SHADER:      return shaderc_glsl_vertex_shader;
                case GL_FRAGMENT_SHADER:    return shaderc_glsl_fragment_shader;
            }

            EXW_LOG_CORE_ERROR("Shader stage {0} is not supported.", _stage);
            EXW_ASSERT_CORE(false);
            return (shaderc_shader_kind)0;
        }

        static constexpr const char* gl_shader_stage_to_string(GLenum _stage)
        {
            switch (_stage)
            {
                case GL_VERTEX_SHADER:      return "GL_VERTEX_SHADER";
                case GL_FRAGMENT_SHADER:    return "GL_FRAGMENT_SHADER";
            }

            EXW_LOG_CORE_ERROR("Shader stage {0} is not supported.", _stage);
            EXW_ASSERT_CORE(false);
            return nullptr;
        }

        static constexpr const char* gl_shader_stage_cached_opengl_file_extexsion(GLenum _stage)
        {
            switch (_stage)
            {
                case GL_VERTEX_SHADER:      return ".cached_opengl_vert";
                case GL_FRAGMENT_SHADER:    return ".cached_opengl_frag";
            }

            EXW_LOG_CORE_ERROR("Shader stage {0} is not supported.", _stage);
            EXW_ASSERT_CORE(false);
            return "";
        }

        static constexpr const char* gl_shader_stage_cached_vulkan_file_extexsion(GLenum _stage)
        {
            switch (_stage)
            {
                case GL_VERTEX_SHADER:      return ".cached_vulkan_vert";
                case GL_FRAGMENT_SHADER:    return ".cached_vulkan_frag";
            }

            EXW_LOG_CORE_ERROR("Shader stage {0} is not supported.", _stage);
            EXW_ASSERT_CORE(false);
            return "";
        }

        static constexpr const char* get_cache_directory()
        {
            // TODO: validate assets directory;
            return "assets/cache/shader/opengl";
        }

        static void try_create_cache_directory()
        {
            std::string cacheDir = get_cache_directory();
            if (!std::filesystem::exists(cacheDir))
                std::filesystem::create_directories(cacheDir);
        }

    }

    namespace graphics
    {
        OpenGLShader::OpenGLShader(const std::string& _filepath)
            : m_Filepath(_filepath)
        {
            utils::try_create_cache_directory();

            std::string source = read_file(_filepath);
            std::unordered_map<uint32_t, std::string> shaderSource = pre_process(source);

            EXW_LOG_CORE_INDENT_IN();
            {
                //Timer timer;
                compile_or_get_vulkan_binaries(shaderSource);
                compile_or_get_opengl_binaries();
                create_program();
                //EXW_LOG_CORE_WARN("Shader creation took {0}ms", timer.elapesd_millis());
            }
            EXW_LOG_CORE_INDENT_OUT();

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

        OpenGLShader::OpenGLShader(const std::string& _name, const std::string& _vertexSource, const std::string& _fragmentSource)
            : m_Name(_name)
        {
            std::unordered_map<uint32_t, std::string> shaderSources;
            shaderSources[GL_VERTEX_SHADER] = _vertexSource;
            shaderSources[GL_FRAGMENT_SHADER] = _fragmentSource;

            EXW_LOG_CORE_INDENT_IN();
            {
                //Timer timer;
                compile_or_get_vulkan_binaries(shaderSources);
                compile_or_get_opengl_binaries();
                create_program();
                //EXW_LOG_CORE_WARN("Shader creation took {0}ms", timer.elapesd_millis());
            }
            EXW_LOG_CORE_INDENT_OUT();
        }

        OpenGLShader::~OpenGLShader()
        {
            glDeleteProgram(m_Renderer_id);
        }

        void OpenGLShader::bind() const
        {
            glUseProgram(m_Renderer_id);
        }

        void OpenGLShader::unbind() const
        {
            glUseProgram(0);
        }
       
        void OpenGLShader::set_int(const std::string& _name, int _value)
        {
            upload_uniform_int(_name, _value);
        }

        void OpenGLShader::set_int_arr(const std::string& _name, int* _values, uint32_t _count)
        {
            upload_uniform_int_arr(_name, _values, _count);
        }

        void OpenGLShader::set_float(const std::string& _name, float _value)
        {
            upload_uniform_float(_name, _value);
        }

        void OpenGLShader::set_float2(const std::string& _name, const maths::vector2& _value)
        {
            upload_uniform_float2(_name, _value);
        }

        void OpenGLShader::set_float3(const std::string& _name, const maths::vector3& _value)
        {
            upload_uniform_float3(_name, _value);
        }

        void OpenGLShader::set_float4(const std::string& _name, const maths::vector4& _value)
        {
            upload_uniform_float4(_name, _value);
        }

        void OpenGLShader::set_matrix4(const std::string& _name, const maths::matrix4& _value)
        {
            upload_uniform_matrix4(_name, _value);
        }

        void OpenGLShader::upload_uniform_int(const std::string& _name, int _value)
        {
            GLint location = glGetUniformLocation(m_Renderer_id, _name.c_str());
            glUniform1i(location, _value);
        }

        void OpenGLShader::upload_uniform_int_arr(const std::string& _name, int* _values, uint32_t _count)
        {
            GLint location = glGetUniformLocation(m_Renderer_id, _name.c_str());
            glUniform1iv(location, _count, _values);
        }

        void OpenGLShader::upload_uniform_float(const std::string& _name, float _value)
        {
            GLint location = glGetUniformLocation(m_Renderer_id, _name.c_str());
            glUniform1f(location, _value);
        }

        void OpenGLShader::upload_uniform_float2(const std::string& _name, const maths::vector2& _value)
        {
            GLint location = glGetUniformLocation(m_Renderer_id, _name.c_str());
            glUniform2f(location, _value.x, _value.y);
        }

        void OpenGLShader::upload_uniform_float3(const std::string& _name, const maths::vector3& _value)
        {
            GLint location = glGetUniformLocation(m_Renderer_id, _name.c_str());
            glUniform3f(location, _value.x, _value.y, _value.z);
        }

        void OpenGLShader::upload_uniform_float4(const std::string& _name, const maths::vector4& _value)
        {
            GLint location = glGetUniformLocation(m_Renderer_id, _name.c_str());
            glUniform4f(location, _value.x, _value.y, _value.z, _value.w);
        }

        void OpenGLShader::upload_uniform_matrix3(const std::string& _name, const maths::matrix3& _value)
        {
            GLint location = glGetUniformLocation(m_Renderer_id, _name.c_str());
            glUniformMatrix3fv(location, 1, GL_FALSE, &(_value[0].x));
        }

        void OpenGLShader::upload_uniform_matrix4(const std::string& _name, const maths::matrix4& _value)
        {
            GLint location = glGetUniformLocation(m_Renderer_id, _name.c_str());
            glUniformMatrix4fv(location, 1, GL_FALSE, &(_value[0].x));
        }

        std::string OpenGLShader::read_file(const std::string& _filepath)
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
 
        std::unordered_map<uint32_t, std::string> OpenGLShader::pre_process(const std::string& _source)
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

        #pragma warning(disable:26812)
        void OpenGLShader::compile_or_get_vulkan_binaries(const std::unordered_map<uint32_t, std::string>& _shaderSource)
        {
            GLuint program = glCreateProgram();

            shaderc::Compiler compiler;
            shaderc::CompileOptions compilerOptions;
            compilerOptions.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
            const bool optimize = true;
            if (optimize)
                compilerOptions.SetOptimizationLevel(shaderc_optimization_level_performance);

            std::filesystem::path cacheDir = utils::get_cache_directory();

            auto& shaderData = m_Vulkan_SPIRV;
            shaderData.clear();
            for (auto&& [stage, source] : _shaderSource)
            {
                std::filesystem::path shaderFilePath = m_Filepath;
                std::filesystem::path cachedPath = cacheDir / (shaderFilePath.filename().string() + utils::gl_shader_stage_cached_vulkan_file_extexsion(stage));

                std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
                if (in.is_open())
                {
                    in.seekg(0, std::ios::end);
                    auto size = in.tellg();
                    in.seekg(0, std::ios::beg);

                    auto& data = shaderData[stage];
                    data.resize(size / sizeof(uint32_t));
                    in.read((char*)data.data(), size);
                }
                else
                {
                    shaderc::SpvCompilationResult result = compiler.CompileGlslToSpv(source, utils::gl_shader_stage_to_shaderc(stage), m_Filepath.c_str(), compilerOptions);
                    if (result.GetCompilationStatus() != shaderc_compilation_status_success)
                    {
                        EXW_LOG_CORE_ERROR(result.GetErrorMessage());
                        EXW_ASSERT_CORE(false);
                    }

                    shaderData[stage] = std::vector<uint32_t>(result.cbegin(), result.cend());

                    std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
                    if (out.is_open())
                    {
                        auto& data = shaderData[stage];
                        out.write((char*)data.data(), data.size() * sizeof(uint32_t));
                        out.flush();
                        out.close();
                    }
                }
            }

            for (auto&& [stage, data] : shaderData)
                reflect(stage, data);
        }
        #pragma warning(restore:26812)

        void OpenGLShader::compile_or_get_opengl_binaries()
        {
            GLuint program = glCreateProgram();

            shaderc::Compiler compiler;
            shaderc::CompileOptions compilerOptions;
            compilerOptions.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
            const bool optimize = false;
            if (optimize)
                compilerOptions.SetOptimizationLevel(shaderc_optimization_level_performance);

            std::filesystem::path cacheDir = utils::get_cache_directory();

            auto& shaderData = m_OpenGL_SPIRV;
            shaderData.clear();
            m_OpenGL_source.clear();
            for (auto&& [stage, spirv] : m_Vulkan_SPIRV)
            {
                std::filesystem::path shaderFilePath = m_Filepath;
                std::filesystem::path cachedPath = cacheDir / (shaderFilePath.filename().string() + utils::gl_shader_stage_cached_opengl_file_extexsion(stage));

                std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
                if (in.is_open())
                {
                    in.seekg(0, std::ios::end);
                    auto size = in.tellg();
                    in.seekg(0, std::ios::beg);

                    auto& data = shaderData[stage];
                    data.resize(size / sizeof(uint32_t));
                    in.read((char*)data.data(), size);
                }
                else
                {
                    spirv_cross::CompilerGLSL CompilerGlsl(spirv);
                    m_OpenGL_source[stage] = CompilerGlsl.compile();
                    auto& source = m_OpenGL_source[stage];

                    shaderc::SpvCompilationResult result = compiler.CompileGlslToSpv(source, utils::gl_shader_stage_to_shaderc(stage), m_Filepath.c_str());
                    if (result.GetCompilationStatus() != shaderc_compilation_status_success)
                    {
                        EXW_LOG_CORE_ERROR(result.GetErrorMessage());
                        EXW_ASSERT_CORE(false);
                    }

                    shaderData[stage] = std::vector<uint32_t>(result.cbegin(), result.cend());

                    std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
                    if (out.is_open())
                    {
                        auto& data = shaderData[stage];
                        out.write((char*)data.data(), data.size() * sizeof(uint32_t));
                        out.flush();
                        out.close();
                    }
                }
            }
        }

        void OpenGLShader::create_program()
        {
            GLuint program = glCreateProgram();

            std::vector<GLuint> shaderIDs;
            for (auto&& [stage, spirv] : m_OpenGL_SPIRV)
            {
                GLuint shaderID = shaderIDs.emplace_back(glCreateShader(stage));
                glShaderBinary(1, &shaderID, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.data(), (GLsizei)(spirv.size() * sizeof(uint32_t)));
                glSpecializeShader(shaderID, "main", 0, nullptr, nullptr);
                glAttachShader(program, shaderID);
            }

            glLinkProgram(program);

            GLint status;
            glGetProgramiv(program, GL_LINK_STATUS, &status);
            if (status == GL_FALSE)
            {
                GLint length;
                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
                std::vector<GLchar> buffer(length);
                glGetProgramInfoLog(program, length, &length, buffer.data());
                EXW_LOG_CORE_ERROR("Shader linking failed: {0}\n({1})", buffer.data(), m_Filepath);

                glDeleteProgram(program);
                for (auto id : shaderIDs)
                    glDeleteShader(id);
            }

            for (auto id : shaderIDs)
            {
                glDetachShader(program, id);
                glDeleteShader(id);
            }

            m_Renderer_id = program;
        }

        void OpenGLShader::reflect(uint32_t _stage, const std::vector<uint32_t>& _shaderData)
        {
            spirv_cross::Compiler compiler(_shaderData);
            spirv_cross::ShaderResources resources = compiler.get_shader_resources();

            EXW_LOG_CORE_TRACE("OpenGLShader::reflect: {0} {1}", utils::gl_shader_stage_to_string(_stage), m_Filepath);
            EXW_LOG_CORE_TRACE("  Resources      : {0}", resources.sampled_images.size());
            EXW_LOG_CORE_TRACE("  Uniform buffers: {0}", resources.uniform_buffers.size());

            for (const auto& uBuffer : resources.uniform_buffers)
            {
                const auto& bufferType = compiler.get_type(uBuffer.base_type_id);
                size_t bufferSize = compiler.get_declared_struct_size(bufferType);
                size_t binding = compiler.get_decoration(uBuffer.id, spv::DecorationBinding);
                int memberCount = bufferType.member_types.size();

                EXW_LOG_CORE_TRACE("    Buffer {0}:", uBuffer.name);
                EXW_LOG_CORE_TRACE("      Size   : {0}", bufferSize);
                EXW_LOG_CORE_TRACE("      Binding: {0}", binding);
                EXW_LOG_CORE_TRACE("      Members: {0}", memberCount);
            }
        }

    }
}


