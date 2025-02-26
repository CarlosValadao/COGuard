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

set(PICO_BOARD pico_w CACHE STRING "Board type")
include(pico_sdk_import.cmake)
project(COGuard C CXX ASM)
pico_sdk_init()
add_executable(COGuard COGuard.c
)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(COGuard 0)
pico_enable_stdio_usb(COGuard 1)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/generated)
pico_generate_pio_header(COGuard ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)
target_sources(COGuard PRIVATE COGuard.c
                lib/mlt8530.c
                lib/mq7.c
                lib/push_button.c
                lib/rgb.c
                lib/ssd1306_utils.c
                lib/ssd1306.c
                lib/ws2812b.c
            )
target_link_libraries(
                COGuard
                pico_stdlib
                hardware_i2c
                hardware_pwm
                hardware_timer
                hardware_adc
                hardware_pio
                hardware_clocks
                )
pico_add_extra_outputs(COGuard)