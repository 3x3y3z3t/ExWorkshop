// ;
#pragma once
#include "Common.h"

#ifdef EXW_PLATFORM_WINDOWS
extern exw::Application* exw::create_application();

int main(int _argc, char* _argv[])
{
    exw::Application* app = exw::create_application();

    app->run();

    delete app;

    return 0;
}

#else

#error "Unsupported platform."

#endif
