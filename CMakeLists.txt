cmake_minimum_required(VERSION 3.21)
project(EngineCore)
include(FetchContent)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE CPP_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}
        "Application/*.cpp"
        "Core/*.cpp")
# OpenSSL
IF(WIN32)
    MESSAGE(WARNING "windows 下自行配置 openssl")
ELSEIF(APPLE OR UNIX)
    SET(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
    SET(OPENSSL_LIBRARIES "/usr/local/opt/openssl/lib")
ENDIF()

# Libevent
SET(EVENT__FORCE_KQUEUE_CHECK True)
FetchContent_Declare(
        Libevent
        GIT_REPOSITORY https://github.com/libevent/libevent.git
        GIT_TAG        release-2.1.12-stable
        GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(Libevent)
FetchContent_GetProperties(Libevent)

add_executable(EngineCore ${CPP_SOURCES})
