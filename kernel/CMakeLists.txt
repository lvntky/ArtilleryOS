# Kernel CMakeLists.txt (artilleryos/kernel/CMakeLists.txt)

add_library(kernel OBJECT
    src/kernel.c
    # Add other source files if any
)

target_include_directories(kernel
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add a dependency on the bootloader target
add_dependencies(kernel /home/levent/Projects/ArtilleryOs/kernel/arch/x64/bootloader)

