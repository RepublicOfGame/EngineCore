add_subdirectory(CodeGen)


add_executable(EHT EngineHeaderTool.cpp Parser.cpp tools.cpp)
target_link_libraries(EHT Util xml2 ${LLVM_LIBRARY_DIRS}/libclang.dylib)
