# kernel/CMakeLists.txt

add_executable(kernel
        src/kernel.c
        # Add other source files if any
)

target_include_directories(kernel
        PUBLIC ${CMAKE_SOURCE_DIR}/kernel/include
)

# Set the output binary name
set_target_properties(kernel PROPERTIES OUTPUT_NAME "kernel.bin")
