// ;
#pragma once

#include "exw\Common.h"
#include "Application.h"

#ifdef EXW_PLATFORM_WINDOWS

    extern exw::Application* exw::create_application();

    int main(int _argc, char* _argv[])
    {
        exw::utils::Log::init();

        EXW_PROFILE_BEGIN_SESSION("Startup", "EXW_Startup.json");
        auto app = exw::create_application();
        EXW_PROFILE_END_SESSION();

        EXW_PROFILE_BEGIN_SESSION("Runtime", "EXW_Runtime.json");
        app->run();
        EXW_PROFILE_END_SESSION();

        EXW_PROFILE_BEGIN_SESSION("Shutdown", "EXW_Shutdown.json");
        delete app;
        EXW_PROFILE_END_SESSION();



        return 0;
    }

#else

    #error "Unsupported platform."

#endif
