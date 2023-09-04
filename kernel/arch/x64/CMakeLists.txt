# Bootloader CMakeLists.txt (kernel/arch/x64/CMakeLists.txt)

# Define a custom target for the bootloader
add_custom_target(bootloader
    COMMAND nasm -f bin -o bootloader.bin bootloader.asm
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    SOURCES bootloader.asm
)
