MACRO(add_core_module module_name)
    aux_source_directory(Private SUB_MODULE)
    add_library(module_name STATIC ${SUB_MODULE})
    target_include_directories(module_name PRIVATE Public)

    SET(CORE_LIB ${CORE_LIB} module_name)
ENDMACRO()

add_subdirectory(UObject)