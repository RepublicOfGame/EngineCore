include_directories(${LLVM_DIR}/include)

add_executable(EHT EngineHeaderTool.cpp Parser.cpp)

target_link_directories(EHT PRIVATE ${LLVM_DIR}/lib)
target_link_libraries(EHT Util libclang)
