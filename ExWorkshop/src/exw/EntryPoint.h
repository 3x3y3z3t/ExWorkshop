/*  EntryPoint.h
*   Version: 1.5 (2022.07.25)
*
*   Previois version
*       v1.2 (EntryPoint.cpp)
* 
*   Contributor
*       Arime-chan
*/

#include "exw\utils\Logger.h"
#include "exw\core\Application.h"

extern exw::Application* exw::create_application(exw::AppCommandLineArgs _args);

int main(int _argc, char* _argv[], char* _envp[])
{
    exw::utils::Logger::init();

    exw::Application* app = nullptr;
    EXW_LOG_CORE_TRACE("Creating Application..");
    EXW_LOG_CORE_INDENT_IN();
    {
        app = exw::create_application({ _argc, _argv });
    }
    EXW_LOG_CORE_INDENT_OUT();
    EXW_LOG_CORE_TRACE("Application created.");

    {
        app->run();
    }

    EXW_LOG_CORE_TRACE("Closing Application..");
    EXW_LOG_CORE_INDENT_IN();
    {
        delete app;
    }
    EXW_LOG_CORE_INDENT_OUT();
    EXW_LOG_CORE_TRACE("Application closed.");


    return 0;
}
