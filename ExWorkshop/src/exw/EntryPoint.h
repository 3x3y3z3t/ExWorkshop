// ;
#pragma once

#include "exw\Common.h"
#include "exw\utils\Log.h"

#ifdef EXW_PLATFORM_WINDOWS

    extern exw::Application* exw::create_application();

    int main(int _argc, char* _argv[])
    {
        exw::utils::Log::init();

        auto app = exw::create_application();

        app->run();

        delete app;



        return 0;
    }

#else

    #error "Unsupported platform."

#endif
