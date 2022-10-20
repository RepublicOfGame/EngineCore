#include "play.h"
#define NFUNCTION(...) __attribute__((annotate("NFUNCTION(__VA_ARGS__)")))
#define NCLASS(...) __attribute__((annotate("NCLASS(__VA_ARGS__)")))
#define NPROPERTY(...) __attribute__((annotate("NPROPERTY(__VA_ARGS__)")))
class MyClass {
  typedef long long LL;
  NFUNCTION()
  int Test(int intA, LL longB) {}
};