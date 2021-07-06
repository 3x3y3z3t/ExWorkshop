// ;
#pragma once

#define EXW_PLATFORM_WINDOWS // TODO: add platform check

#ifdef EXW_PLATFORM_WINDOWS

int main(int _argc, char* _argv[])
{

    return 0;
}

#else

#error "Unsupported platform."

#endif
