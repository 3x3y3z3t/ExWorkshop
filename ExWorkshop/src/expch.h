// ;
#pragma once

#include <stdint.h>

#include <fstream>
#include <sstream>

#include <chrono>
#include <filesystem>
#include <functional>
#include <memory>
#include <random>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "exw\Common.h"
#include "exw\utils\Log.h"
#include "exw\utils\Instrumentor.h"

#ifdef EXW_PLATFORM_WINDOWS
    #include <Windows.h>
#endif
