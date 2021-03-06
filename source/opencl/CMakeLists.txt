find_package(OpenCL REQUIRED)

include_directories(${OpenCL_INCLUDE_DIRS})

set(sources "")

set(targets
    info
    saxpy
)

foreach(filename IN LISTS targets)
    set(target "opencl-${filename}")

    set(target_sources ${sources} "${filename}.cpp")

    add_executable(${target} ${target_sources})
    target_link_libraries(${target} ${OpenCL_LIBRARIES} utilgpu::cpp utilgpu::cl)

    target_compile_options(${target} PRIVATE ${DEFAULT_COMPILE_FLAGS})

    option(CLANG_FORMAT "Add clang formatting to the build step" ON)
    if (CLANG_FORMAT)
        add_custom_target("format-${target}"
            COMMAND clang-format -i ${target_sources}
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
            COMMENT "Formatting code"
            VERBATIM)
        add_dependencies(${target} "format-${target}")
    endif()
endforeach()
