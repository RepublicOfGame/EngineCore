file(GLOB_RECURSE UTIL_CPP_SOURCES "Private/*.cpp")

add_library(Util STATIC ${UTIL_CPP_SOURCES})