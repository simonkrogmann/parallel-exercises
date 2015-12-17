set(sources
    main.cpp
)

add_executable(main ${sources})

target_compile_options(main PRIVATE ${DEFAULT_COMPILE_FLAGS})
