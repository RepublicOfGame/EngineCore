#pragma once

#include "spdlog/spdlog.h"
#include "InitOnce.h"

#define Loge SPDLOG_ERROR
#define Logi SPDLOG_INFO
#define Logw SPDLOG_WARN
#define Logd SPDLOG_DEBUG

namespace Util{
    static void InitLog(){
        spdlog::set_pattern("[%^%l%$] [%s:%#] [%H:%M:%S.%e] %v");
    }
}