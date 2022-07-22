/*  EntryPoint.h
*   Version: 1.4 (2022.07.22)
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

    exw::Application* app = exw::create_application({ _argc, _argv });
    EXW_LOG_CORE_TRACE("Application created.");
    
    app->run();

    delete app;


    return 0;
}
