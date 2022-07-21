/*  Logger.h
*   Version: 1.1 (2022.07.21)
*
*   Contributor
*       Arime-chan
*/

#pragma once

#include "ExWorkshop\Common.h"

#pragma warning(push, 0)
#include <spdlog\spdlog.h>
#include <spdlog\fmt\ostr.h>
#pragma warning(pop)

namespace exw
{
    namespace utils
    {
        class Logger
        {
        public:
            static void init();

            static refs::Ref<spdlog::logger>& get_core_logger() { return s_Core_logger; }
            static refs::Ref<spdlog::logger>& get_client_logger() { return s_Client_logger; }

        private:
            static refs::Ref<spdlog::logger> s_Core_logger;
            static refs::Ref<spdlog::logger> s_Client_logger;

        };

    }
}

#define EXW_CORE_LOG_DEBUG(...)     exw::utils::Logger::get_core_logger()->debug(__VA_ARGS__)
#define EXW_CORE_LOG_TRACE(...)     exw::utils::Logger::get_core_logger()->trace(__VA_ARGS__)
#define EXW_CORE_LOG_INFO(...)      exw::utils::Logger::get_core_logger()->info(__VA_ARGS__)
#define EXW_CORE_LOG_WARN(...)      exw::utils::Logger::get_core_logger()->warn(__VA_ARGS__)
#define EXW_CORE_LOG_ERROR(...)     exw::utils::Logger::get_core_logger()->error(__VA_ARGS__)
#define EXW_CORE_LOG_CRITICAL(...)  exw::utils::Logger::get_core_logger()->critical(__VA_ARGS__)

#define EXW_LOG_DEBUG(...)          exw::utils::Logger::get_client_logger()->debug(__VA_ARGS__)
#define EXW_LOG_TRACE(...)          exw::utils::Logger::get_client_logger()->trace(__VA_ARGS__)
#define EXW_LOG_INFO(...)           exw::utils::Logger::get_client_logger()->info(__VA_ARGS__)
#define EXW_LOG_WARN(...)           exw::utils::Logger::get_client_logger()->warn(__VA_ARGS__)
#define EXW_LOG_ERROR(...)          exw::utils::Logger::get_client_logger()->error(__VA_ARGS__)
#define EXW_LOG_CRITICAL(...)       exw::utils::Logger::get_client_logger()->critical(__VA_ARGS__)
