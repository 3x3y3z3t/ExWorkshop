/*  OpenGLRendererAPI.cpp
*   Version: 1.0 (2022.07.24)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "OpenGLRendererAPI.h"

#include "exw\utils\Logger.h"

#include <glad\gl.h>

namespace exw
{
    namespace graphics
    {
        void opengl_message_callback(uint32_t _source, uint32_t _type, uint32_t _id, uint32_t _severity, int _length, const char* _message, const void* _userParam)
        {
            switch (_severity)
            {
                case GL_DEBUG_SEVERITY_HIGH:            EXW_LOG_CORE_CRITICAL(_message); return;
                case GL_DEBUG_SEVERITY_MEDIUM:          EXW_LOG_CORE_ERROR(_message); return;
                case GL_DEBUG_SEVERITY_LOW:             EXW_LOG_CORE_WARN(_message); return;
                case GL_DEBUG_SEVERITY_NOTIFICATION:    EXW_LOG_CORE_TRACE(_message); return;
            }

            EXW_LOG_CORE_WARN("Unknown severity level {0}, log as warning:", _severity);
            EXW_LOG_CORE_WARN(_message);
        }

        void OpenGLRendererAPI::init()
        {
            #ifdef EXW_DBG
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(opengl_message_callback, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
            #endif

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glEnable(GL_DEPTH_TEST);
            glEnable(GL_LINE_SMOOTH);
        }

        void OpenGLRendererAPI::clear()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void OpenGLRendererAPI::draw_indexed(const refs::Ref<VertexArray> _vertexArray, uint32_t _indexCount)
        {
            _vertexArray->bind();

            uint32_t count;
            if (_indexCount != 0)
                count = _indexCount;
            else
                count = _vertexArray->get_index_buffer()->get_count();

            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        }

        void OpenGLRendererAPI::draw_lines(const refs::Ref<VertexArray> _vertexArray, uint32_t _vertexCount)
        {
            _vertexArray->bind();
            glDrawArrays(GL_LINES, 0, _vertexCount);
        }

        void OpenGLRendererAPI::set_viewport(uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height)
        {
            glViewport(_x, _y, _width, _height);
        }

        void OpenGLRendererAPI::set_clear_color(maths::vector4 _color)
        {
            glClearColor(_color.r, _color.g, _color.b, _color.a);
        }

        void OpenGLRendererAPI::set_line_width(float _width)
        {
            glLineWidth(_width);
        }

    }
}
