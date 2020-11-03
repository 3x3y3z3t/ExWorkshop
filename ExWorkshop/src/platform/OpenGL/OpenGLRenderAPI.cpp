// ;
#include "expch.h"
#include "OpenGLRenderAPI.h"

#include <glad\glad.h>

namespace exw
{
    namespace graphics
    {
        void opengl_message_callback(uint32_t _src, uint32_t _type, uint32_t _id, uint32_t _severity, int _length, const char* _msg, const void* _userParam)
        {
            switch (_severity)
            {
                case GL_DEBUG_SEVERITY_NOTIFICATION:    EXW_LOG_TRACE(_msg); return;
                case GL_DEBUG_SEVERITY_LOW:             EXW_LOG_WARNING(_msg); return;
                case GL_DEBUG_SEVERITY_MEDIUM:          EXW_LOG_ERROR(_msg); return;
                case GL_DEBUG_SEVERITY_HIGH:            EXW_LOG_CRITICAL(_msg); return;
            }

            EXW_LOG_WARNING("Unknown severity level ({0}).", _severity);
        }

        void OpenGLRenderAPI::init()
        {
            EXW_PROFILE_FUNCTION();
            #if EXW_DBG
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(opengl_message_callback, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
            #endif

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_DEPTH_TEST);
        }

        void OpenGLRenderAPI::clear()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void OpenGLRenderAPI::draw_indexed(const refs::ref<VertexArray>& _vertexArray, uint32_t _indexCount)
        {
            EXW_PROFILE_FUNCTION();
            // NOTICE: Send them to the other side!!;
            auto vibcount = (_indexCount != 0)? _indexCount : _vertexArray->get_index_buffer()->count();
            glDrawElements(GL_TRIANGLES, vibcount, GL_UNSIGNED_INT, nullptr);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void OpenGLRenderAPI::set_viewport(uint32_t _x, uint32_t _y, uint32_t _w, uint32_t _h)
        {
            glViewport(_x, _y, _w, _h);
        }

        void OpenGLRenderAPI::set_clear_color(const maths::vector4& _color)
        {
            glClearColor(_color.r, _color.g, _color.b, _color.a);
        }
    }
}
