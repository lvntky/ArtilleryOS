# kernel/arch/x64/CMakeLists.txt

add_custom_target(bootloader
        COMMAND nasm -f bin -o bootloader.bin bootloader.asm
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        SOURCES bootloader.asm
)

# Specify dependencies
add_dependencies(bootloader kernel)
