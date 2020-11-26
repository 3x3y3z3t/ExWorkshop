// using chrome://tracing/;
#pragma once

#include "exw\utils\Log.h"

//#include <fstream>
//#include <sstream>

//#include <chrono>
//#include <string>

//#include <mutex>
//#include <thread>

#define EXW_ENABLE_PROFILING 0

namespace exw
{
    namespace utils
    {
        using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

        struct ProfileResult
        {
            std::string Name;
            FloatingPointMicroseconds StartTime;
            FloatingPointMicroseconds ElapsedTime;
            std::thread::id ThreadId;
        };

        struct InstrumentationSession
        {
            std::string Name;
        };

        class Instrumentor
        {
        public:
            Instrumentor(const Instrumentor& _instrumentor) = delete;
            Instrumentor(Instrumentor&& _instrumentor) = delete;

        public:
            void begin_session(const std::string& _name, const std::string& _filepath = "result.json")
            {
                std::lock_guard lock(m_Mutex);
                if (m_Current_session != nullptr)
                {
                    if (Log::get_core_logger() != nullptr)
                    {
                        EXW_LOG_ERROR("Instrumentor::begin_session() -> session '{0}' is already open, session '{1}' opening attempt failure.", m_Current_session->Name, _name);
                    }
                    internal_end_session();
                }

                m_Output_stream.open(_filepath);
                if (m_Output_stream.is_open())
                {
                    m_Current_session = new InstrumentationSession({ _name });
                    write_header();
                }
                else
                {
                    if (Log::get_core_logger() != nullptr)
                    {
                        EXW_LOG_ERROR("Instrumentor::begin_session() -> result file at '{0}' opening attempt failure.", _filepath);
                    }
                }
            }

            void end_session()
            {
                std::lock_guard lock(m_Mutex);
                internal_end_session();
            }

            void write_profile(const ProfileResult& _result)
            {
                std::stringstream res;
                res << std::setprecision(3) << std::fixed;
                res << ",{";
                res << "\"cat\":\"function\",";
                res << "\"dur\":" << (_result.ElapsedTime.count()) << ',';
                res << "\"name\":\"" << _result.Name << "\",";
                res << "\"ph\":\"X\",";
                res << "\"pid\":0,";
                res << "\"tid\":" << _result.ThreadId << ",";
                res << "\"ts\":" << _result.StartTime.count();
                res << "}";

                std::lock_guard lock(m_Mutex);
                if (m_Current_session != nullptr)
                {
                    m_Output_stream << res.str();
                    m_Output_stream.flush();
                }
            }

            static Instrumentor& get()
            {
                static Instrumentor instance;
                return instance;
            }

        private:
            Instrumentor()
                : m_Current_session(nullptr)
            {}

            ~Instrumentor()
            {
                end_session();
            }

            void write_header()
            {
                m_Output_stream << "{\"otherData\": {},\"traceEvents\":[{}";
                m_Output_stream.flush();
            }

            void write_footer()
            {
                m_Output_stream << "]}";
                m_Output_stream.flush();
            }

            void internal_end_session()
            {
                if (m_Current_session != nullptr)
                {
                    write_footer();
                    m_Output_stream.close();

                    delete m_Current_session;
                    m_Current_session = nullptr;
                }
            }

        private:
            InstrumentationSession* m_Current_session = nullptr;
            std::mutex m_Mutex;
            std::ofstream m_Output_stream;
        };

        class InstrumentationTimer
        {
        public:
            InstrumentationTimer(const char* _name)
                : m_Name(_name)
            {
                m_Start_timepoint = std::chrono::steady_clock::now();
            }

            ~InstrumentationTimer()
            {
                if (!m_Stopped)
                {
                    stop();
                }
            }

        public:
            void stop()
            {
                using namespace std::chrono;
                auto endTimepoint = steady_clock::now();
                auto highresStartpoint = FloatingPointMicroseconds { m_Start_timepoint.time_since_epoch() };
                auto elapsedTime = time_point_cast<microseconds>(endTimepoint).time_since_epoch() - time_point_cast<microseconds>(m_Start_timepoint).time_since_epoch();

                Instrumentor::get().write_profile({ m_Name, highresStartpoint, elapsedTime, std::this_thread::get_id() });

                m_Stopped = true;
            }

        private:
            const char* m_Name = "";
            bool m_Stopped = false;
            std::chrono::time_point<std::chrono::steady_clock> m_Start_timepoint;
        };
    }

    namespace InstrumetorUtils
    {

        template <size_t N>
        struct ChangeResult
        {
            char Data[N];
        };

        template <size_t N, size_t K>
        constexpr auto cleanup_output_string(const char(&_expr)[N], const char(&_remove)[K])
        {
            ChangeResult<N> res = {};
            size_t srcIndex = 0U;
            size_t dstIndex = 0U;

            while (srcIndex < N)
            {
                size_t matchIndex = 0U;
                while (matchIndex < K - 1U && srcIndex + matchIndex < N - 1U && _expr[srcIndex + matchIndex] == _remove[matchIndex])
                {
                    ++matchIndex;
                }
                if (matchIndex == K - 1U)
                {
                    srcIndex += matchIndex;
                }

                res.Data[dstIndex++] = (_expr[srcIndex] == '"') ? '\'' : _expr[srcIndex];
                ++srcIndex;
            }

            return res;
        }
    }
}

#if EXW_ENABLE_PROFILING

    #pragma region Compiler Detector
    #if (defined(__GNUC__)) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
        #define EXW_FUNC_SIG __PRETTY_FUNCTION__
    #elif (defined(__DMC__) && (__DMC__ >= 0x810))
        #define EXW_FUNC_SIG __PRETTY_FUNCTION__
    #elif (defined(__FUNCSIG__) || (_MSC_VER_))
        #define EXW_FUNC_SIG __FUNCSIG__
    #elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
        #define EXW_FUNC_SIG __FUNCTION__
    #elif (defined(__BORLANDC__) && (__BORLANDC__ >= 0x550))
        #define EXW_FUNC_SIG __FUNC__
    #elif (defined(__STDC_VERSION__) && (__STDC_VERSION__ > 199901))
        #define EXW_FUNC_SIG __func__
    #elif (defined(__cplusplus) && (__cplusplus >= 201103))
        #define EXW_FUNC_SIG __func__
    #else
        #define EXW_FUNC_SIG "unknown FUNC_SIG"
    #endif
    #pragma endregion

    #define EXW_PROFILE_SCOPE_LINE_IMPL(_name, _line)                                                                \
        constexpr auto fixedName##_line = ::exw::InstrumetorUtils::cleanup_output_string(_name, "__cdecl ");     \
        ::exw::utils::InstrumentationTimer timer##_line(fixedName##_line.Data)

    #define EXW_PROFILE_BEGIN_SESSION(_name, _filepath)     ::exw::utils::Instrumentor::get().begin_session(_name, _filepath)
    #define EXW_PROFILE_END_SESSION()                       ::exw::utils::Instrumentor::get().end_session()
    #define EXW_PROFILE_SCOPE_LINE(_name, _line)            EXW_PROFILE_SCOPE_LINE_IMPL(_name, _line)
    #define EXW_PROFILE_SCOPE(_name)                        EXW_PROFILE_SCOPE_LINE(_name, __LINE__)
    #define EXW_PROFILE_FUNCTION()                          EXW_PROFILE_SCOPE(EXW_FUNC_SIG)
#else
    #define EXW_PROFILE_BEGIN_SESSION(_name, _filepath)
    #define EXW_PROFILE_END_SESSION()
    #define EXW_PROFILE_SCOPE(_name)
    #define EXW_PROFILE_FUNCTION()
#endif
