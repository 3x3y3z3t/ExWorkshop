// ;
#include "expch.h"
#include "exw\utils\Log.h"

#include <spdlog\sinks\stdout_color_sinks.h>
#include <spdlog\sinks\basic_file_sink.h>

namespace exw
{
    namespace utils
    {
        refs::ref<spdlog::logger> Log::s_Core_logger;
        refs::ref<spdlog::logger> Log::s_Client_logger;

        void Log::init()
        {
            std::vector<spdlog::sink_ptr> logSinks;
            logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
            logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Log.log", true));

            logSinks[0]->set_pattern("%^[%C.%m.%d %T][%n - thread %-5t]: %v%$");
            logSinks[1]->set_pattern("%^[%C.%m.%d %T][%n - thread %-5t]: %v%$");
            s_Core_logger = refs::create_ref<spdlog::logger>("EXW", begin(logSinks), end(logSinks));
            s_Core_logger->set_level(spdlog::level::trace);
            s_Core_logger->flush_on(spdlog::level::trace);
            spdlog::register_logger(s_Core_logger);

            s_Client_logger = refs::create_ref<spdlog::logger>("app", begin(logSinks), end(logSinks));
            s_Client_logger->set_level(spdlog::level::trace);
            s_Client_logger->flush_on(spdlog::level::trace);
            spdlog::register_logger(s_Client_logger);

            EXW_LOG_INFO("Logger initialized.");
        }
    }
}
