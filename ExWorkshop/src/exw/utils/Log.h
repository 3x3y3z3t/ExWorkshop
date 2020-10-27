// ;
#pragma once

#include "exw\Common.h"

#pragma warning(push, 0)
#include <spdlog\spdlog.h>
#include <spdlog\fmt\ostr.h>
#pragma warning(pop)

namespace exw
{
    namespace utils
    {
        class Log
        {
        public:
            static void init();

            static refs::ref<spdlog::logger>& get_core_logger() { return s_Core_logger; }
            static refs::ref<spdlog::logger>& get_client_logger() { return s_Client_logger; }

        private:
            static refs::ref<spdlog::logger> s_Core_logger;
            static refs::ref<spdlog::logger> s_Client_logger;
        };
    }
}

#ifdef EXW_CORE_LIB
#define EXW_LOG_TRACE(...)      ::exw::utils::Log::get_core_logger()->trace(__VA_ARGS__)
#define EXW_LOG_DEBUG(...)      ::exw::utils::Log::get_core_logger()->debug(__VA_ARGS__)
#define EXW_LOG_INFO(...)       ::exw::utils::Log::get_core_logger()->info(__VA_ARGS__)
#define EXW_LOG_WARNING(...)    ::exw::utils::Log::get_core_logger()->warn(__VA_ARGS__)
#define EXW_LOG_ERROR(...)      ::exw::utils::Log::get_core_logger()->error(__VA_ARGS__)
#define EXW_LOG_CRITICAL(...)   ::exw::utils::Log::get_core_logger()->critical(__VA_ARGS__)
#else
#define EXW_LOG_TRACE(...)      ::exw::utils::Log::get_client_logger()->trace(__VA_ARGS__)
#define EXW_LOG_DEBUG(...)      ::exw::utils::Log::get_client_logger()->debug(__VA_ARGS__)
#define EXW_LOG_INFO(...)       ::exw::utils::Log::get_client_logger()->info(__VA_ARGS__)
#define EXW_LOG_WARNING(...)    ::exw::utils::Log::get_client_logger()->warn(__VA_ARGS__)
#define EXW_LOG_ERROR(...)      ::exw::utils::Log::get_client_logger()->error(__VA_ARGS__)
#define EXW_LOG_CRITICAL(...)   ::exw::utils::Log::get_client_logger()->critical(__VA_ARGS__)
#endif

#ifndef EXW_DBG
#define EXW_LOG_DEBUG(...) 
#define EXW_LOG_TRACE(...)
#endif
