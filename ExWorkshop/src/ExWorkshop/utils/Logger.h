/*  Logger.h
*   Version: 1.2 (2022.07.22)
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

int main(int _argc, char* _argv[], char* _envp[]);

namespace exw
{
    namespace utils
    {
        class Logger
        {
        public:

            #pragma region Core Logger Public Functions
            static void core_indent_in() { ++s_Indent_core; }
            static void core_indent_out() { --s_Indent_core; }

            template<typename ... Args>
            static void core_debug(const std::string& _format, Args&& ... _args)
            {
                s_Logger_core->debug(std::string(s_Indent_core * 2Ui16, ' ').append(_format), std::forward<Args>(_args)...);
            }

            template<typename ... Args>
            static void core_trace(const std::string& _format, Args&& ... _args)
            {
                s_Logger_core->trace(std::string(s_Indent_core * 2Ui16, ' ').append(_format), std::forward<Args>(_args)...);
            }

            template<typename ... Args>
            static void core_info(const std::string& _format, Args&& ... _args)
            {
                s_Logger_core->info(std::string(s_Indent_core * 2Ui16, ' ').append(_format), std::forward<Args>(_args)...);
            }

            template<typename ... Args>
            static void core_warn(const std::string& _format, Args&& ... _args)
            {
                s_Logger_core->warn(std::string(s_Indent_core * 2Ui16, ' ').append(_format), std::forward<Args>(_args)...);
            }

            template<typename ... Args>
            static void core_error(const std::string& _format, Args&& ... _args)
            {
                s_Logger_core->error(std::string(s_Indent_core * 2Ui16, ' ').append(_format), std::forward<Args>(_args)...);
            }

            template<typename ... Args>
            static void core_critical(const std::string& _format, Args&& ... _args)
            {
                s_Logger_core->critical(std::string(s_Indent_core * 2Ui16, ' ').append(_format), std::forward<Args>(_args)...);
            }
            #pragma endregion

            #pragma region Client Logger Public Functions
            static void client_indent_in() { ++s_Indent_client; }
            static void client_indent_out() { --s_Indent_client; }

            template<typename ... Args>
            static void client_debug(const std::string& _format, Args&& ... _args)
            {
                s_Logger_client->debug(std::string(s_Indent_core * 2Ui16, ' ').append(_format), std::forward<Args>(_args)...);
            }

            template<typename ... Args>
            static void client_trace(const std::string& _format, Args&& ... _args)
            {
                s_Logger_client->trace(std::string(s_Indent_core * 2Ui16, ' ').append(_format), std::forward<Args>(_args)...);
            }

            template<typename ... Args>
            static void client_info(const std::string& _format, Args&& ... _args)
            {
                s_Logger_client->info(std::string(s_Indent_core * 2Ui16, ' ').append(_format), std::forward<Args>(_args)...);
            }

            template<typename ... Args>
            static void client_warn(const std::string& _format, Args&& ... _args)
            {
                s_Logger_client->warn(std::string(s_Indent_core * 2Ui16, ' ').append(_format), std::forward<Args>(_args)...);
            }

            template<typename ... Args>
            static void client_error(const std::string& _format, Args&& ... _args)
            {
                s_Logger_client->error(std::string(s_Indent_core * 2Ui16, ' ').append(_format), std::forward<Args>(_args)...);
            }

            template<typename ... Args>
            static void client_critical(const std::string& _format, Args&& ... _args)
            {
                s_Logger_client->critical(std::string(s_Indent_core * 2Ui16, ' ').append(_format), std::forward<Args>(_args)...);
            }
            #pragma endregion

        private:
            static void init();

        private:
            static uint8_t s_Indent_core;
            static uint8_t s_Indent_client;

            static refs::Ref<spdlog::logger> s_Logger_core;
            static refs::Ref<spdlog::logger> s_Logger_client;

            friend int ::main(int _argc, char* _argv[], char* _envp[]);
        };

    }
}

#define EXW_LOG_CORE_TRACE(...)             exw::utils::Logger::core_trace(__VA_ARGS__)
#define EXW_LOG_CORE_DEBUG(...)             exw::utils::Logger::core_debug(__VA_ARGS__)
#define EXW_LOG_CORE_INFO(...)              exw::utils::Logger::core_info(__VA_ARGS__)
#define EXW_LOG_CORE_WARN(...)              exw::utils::Logger::core_warn(__VA_ARGS__)
#define EXW_LOG_CORE_ERROR(...)             exw::utils::Logger::core_error(__VA_ARGS__)
#define EXW_LOG_CORE_CRITICAL(...)          exw::utils::Logger::core_critical(__VA_ARGS__)
#define EXW_LOG_CORE_INDENT_IN()            exw::utils::Logger::core_indent_in();
#define EXW_LOG_CORE_INDENT_OUT()           exw::utils::Logger::core_indent_out();

#define EXW_LOG_TRACE(...)                  exw::utils::Logger::client_trace(__VA_ARGS__)
#define EXW_LOG_DEBUG(...)                  exw::utils::Logger::client_debug(__VA_ARGS__)
#define EXW_LOG_INFO(...)                   exw::utils::Logger::client_info(__VA_ARGS__)
#define EXW_LOG_WARN(...)                   exw::utils::Logger::client_warn(__VA_ARGS__)
#define EXW_LOG_ERROR(...)                  exw::utils::Logger::client_error(__VA_ARGS__)
#define EXW_LOG_CRITICAL(...)               exw::utils::Logger::client_critical(__VA_ARGS__)
#define EXW_LOG_INDENT_IN()                 exw::utils::Logger::client_indent_in();
#define EXW_LOG_INDENT_OUT()                exw::utils::Logger::client_indent_out();
