/*  EntryPoint.cpp
*   Version: 1.1 (2022.05.25)
*
*   Contributor
*       Arime-chan
*/

#include "exwpch.h"

#include "utils\Logger.h"


int main(int _argc, char* _argv[], char* _envp[])
{
    exw::utils::Logger::init();


    EXW_CORE_LOG_DEBUG(">> ExWorkshop Entry Point <<");
    EXW_CORE_LOG_TRACE(">> ExWorkshop Entry Point <<");
    EXW_CORE_LOG_INFO(">> ExWorkshop Entry Point <<");
    EXW_CORE_LOG_WARN(">> ExWorkshop Entry Point <<");
    EXW_CORE_LOG_ERROR(">> ExWorkshop Entry Point <<");
    EXW_CORE_LOG_CRITICAL(">> ExWorkshop Entry Point <<");






    return 0;
}
