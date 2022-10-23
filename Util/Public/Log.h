#pragma once

#include "InitOnce.h"
#include "spdlog/spdlog.h"

#define Loge SPDLOG_ERROR
#define Logi SPDLOG_INFO
#define Logw SPDLOG_WARN
#define Logd SPDLOG_DEBUG

#define LogSystemCallError()                                                   \
  char buf[512];                                                               \
  strerror_s(buf, 512, errno);                                                 \
  Logd(buf)

namespace Util {
static void InitLog() {
  spdlog::set_pattern("[%^%l%$] [%s:%#] [%H:%M:%S.%e] %v");
}
} // namespace Util