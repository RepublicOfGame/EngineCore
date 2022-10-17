#pragma once

#include "XXH64.h"
#include <string>

#define StringHashSeed 1008612

typedef uint64_t RID;

int constexpr length(const char *str) {
    return *str ? 1 + length(str + 1) : 0;
}

consteval RID StringToRID(const char *s, size_t len) {
    return xxh64::hash(s, len, StringHashSeed);
}

consteval RID StringToRID(const char *s) {
    return StringToRID(s, length(s));
}