find_package(OpenCL REQUIRED)

include_directories(${OpenCL_INCLUDE_DIRS})

set(target opencl-exercises)

set(sources
    main.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target} ${OpenCL_LIBRARIES})

target_compile_options(${target} PRIVATE ${DEFAULT_COMPILE_FLAGS})

option(CLANG_FORMAT "Add clang formatting to the build step" ON)
if (CLANG_FORMAT)
    add_custom_target("format-${target}"
        COMMAND clang-format -i ${sources}
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        COMMENT "Formatting code"
        VERBATIM)
    add_dependencies(${target} "format-${target}")
endif()
