/*  Logger.cpp
*   Version: 1.1 (2022.07.20)
*
*   Contributor
*       Arime-chan
*/
#include "exwpch.h"
#include "Logger.h"

#include <spdlog\sinks\stdout_color_sinks.h>
#include <spdlog\sinks\basic_file_sink.h>

namespace exw
{
    namespace utils
    {
        refs::Ref<spdlog::logger> Logger::s_Core_logger;
        refs::Ref<spdlog::logger> Logger::s_Client_logger;

        void Logger::init()
        {
            time_t secs = std::time(nullptr);
            std::tm* tm = std::localtime(&secs);

            char buffer[64] = { 0 };
            sprintf_s(buffer, "ExWorkshop_%d%02d%02d_%02d%02d%02d.log", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

            std::vector<spdlog::sink_ptr> sinks;
            sinks.emplace_back(refs::create_ref<spdlog::sinks::stdout_color_sink_mt>());
            sinks.emplace_back(refs::create_ref<spdlog::sinks::basic_file_sink_mt>(buffer, true)); // truncate = true;

            sinks[0]->set_pattern("%^[%C.%m.%d %H:%M:%S.%e][%t][%n] %v%$");
            sinks[1]->set_pattern("[%C.%m.%d %H:%M:%S.%e][%t][%n][%-8l] %v");

            s_Core_logger = refs::create_ref<spdlog::logger>("CORE", std::begin(sinks), std::end(sinks));
            spdlog::register_logger(s_Core_logger);
            s_Core_logger->set_level(spdlog::level::trace);
            s_Core_logger->flush_on(spdlog::level::trace);

            s_Client_logger = refs::create_ref<spdlog::logger>("APP ", std::begin(sinks), std::end(sinks));
            spdlog::register_logger(s_Client_logger);
            s_Client_logger->set_level(spdlog::level::trace);
            s_Client_logger->flush_on(spdlog::level::trace);
        }
    }
}
