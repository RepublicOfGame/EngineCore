add_library(TestPlugin SHARED
        TestPlugin.cpp
)

target_link_libraries(TestPlugin ${llvm_libs} ${clang_libs})

install(TARGETS TestPlugin DESTINATION lib)
