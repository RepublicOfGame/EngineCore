add_executable(EHT EngineHeaderTool.cpp)
target_link_libraries(EHT Util ${LLVM_LIBRARY_DIRS}/libclang.dylib)
