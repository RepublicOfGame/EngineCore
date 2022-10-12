cmake_minimum_required(VERSION 3.21)
project(EngineCore)
include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
#add_compile_options(-v)

file(GLOB_RECURSE CPP_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}
        "Application/*.cpp"
        "Core/*.cpp")

include_directories(
        ${CMAKE_SOURCE_DIR}/Core/Util/Public
        ${CMAKE_SOURCE_DIR}/Core/Net/Public
)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

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
# spdlog 日志库
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG        v1.x
        GIT_SHALLOW    TRUE
)
# Googletest
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(libevent spdlog googletest)
include_directories(${libevent_SOURCE_DIR}/include/)
include_directories(${libevent_BINARY_DIR}/include/)
include_directories(${spdlog_SOURCE_DIR}/include/)


# LLVM
SET(LLVM_DIR /usr/local/Cellar/llvm/13.0.0_1/lib/cmake/llvm)
find_package(LLVM REQUIRED CONFIG)
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

# Clang
SET(Clang_DIR /usr/local/Cellar/llvm/13.0.0_1/lib/cmake/clang)
find_package(Clang REQUIRED)

message("LLVM STATUS:
  Definitions ${LLVM_DEFINITIONS}
  Includes    ${LLVM_INCLUDE_DIRS}
              ${CLANG_INCLUDE_DIRS}
  Libraries   ${LLVM_LIBRARY_DIRS}"
)

# 添加 LLVM 和 Clang 的头文件和链接库
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs support)
list(APPEND clang_libs clangBasic clangAST clangFrontend clangLex)

# Compiler Plugin
add_subdirectory(CompilerPlugin)

# 主程序
add_executable(EngineCore ${CPP_SOURCES})
add_dependencies(EngineCore TestPlugin)
target_compile_options(EngineCore PRIVATE -fplugin=${PROJECT_BINARY_DIR}/lib/libTestPlugin.dylib)

# Unit Test
file(GLOB_RECURSE CPP_TEST_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}
        "Test/*.cpp")

add_executable(EngineTest ${CPP_TEST_SOURCES})
target_link_libraries(EngineTest GTest::gtest_main)
enable_testing()

include(GoogleTest)
gtest_discover_tests(EngineTest)