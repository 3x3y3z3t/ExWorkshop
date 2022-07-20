/*  EntryPoint.cpp
*   Version: 1.2 (2022.07.20)
*
*   Contributor
*       Arime-chan
*/

#include "exwpch.h"

#include "utils\Logger.h"
#include "ExWorkshop\Core\Application.h"

extern exw::Application* exw::create_application(AppCommandLineArgs _args);

int main(int _argc, char* _argv[], char* _envp[])
{
    exw::utils::Logger::init();

    exw::Application* app = exw::create_application({ _argc, _argv });
    EXW_CORE_LOG_TRACE("Application created.");
    
    app->run();

    app->close();
    EXW_CORE_LOG_TRACE("Application closed.");


    return 0;
}

exw::Application* exw::create_application(AppCommandLineArgs _args)
{
    return new Application("ExWorkshop App", ".", _args);
}
