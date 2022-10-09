#pragma once

#include "spdlog/spdlog.h"
#include "InitOnce.h"

#define ERROR SPDLOG_ERROR
#define INFO SPDLOG_INFO
#define WARN SPDLOG_WARN
#define DEBUG SPDLOG_DEBUG

namespace Util{
    static void InitLog(){
        spdlog::set_pattern("[%^%l%$] [%s:%#] [%H:%M:%S.%e] %v");
    }
}

InitOnce(Util::InitLog);
