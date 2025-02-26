# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico CACHE STRING "Board type")

include(pico_sdk_import.cmake)
project(COGuard C CXX ASM)
pico_sdk_init()
add_executable(COGuard COGuard.c)
pico_set_program_name(COGuard "COGuard")
pico_set_program_version(COGuard "0.1")

# pico_enable_stdio_uart(COGuard 0)
# pico_enable_stdio_usb(COGuard 1)

target_link_libraries(COGuard pico_stdlib)
target_include_directories(COGuard PRIVATE   ${CMAKE_CURRENT_LIST_DIR})
pico_add_extra_outputs(COGuard)