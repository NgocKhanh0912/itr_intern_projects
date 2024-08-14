cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME pulse_oximetry)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    Core/User/bsp/bsp_adc.c
    Core/User/bsp/bsp_callback.c
    Core/User/bsp/bsp_timer.c
    Core/User/bsp/bsp_gpio.c
    Core/User/bsp/bsp_utils.c
    Core/User/bsp/bsp_i2c.c
    Core/User/bsp/bsp_uart.c
    Core/User/bsp/bsp_flash.c
    Core/User/bsp/bsp_serial.c
    Core/User/drv/drv_hr.c
    Core/User/drv/drv_button.c
    Core/User/drv/drv_buzzer.c
    Core/User/drv/drv_ssd1306.c
    Core/User/drv/drv_ds1307.c
    Core/User/middleware/cbuffer.c
    Core/User/middleware/ssd1306_fonts.c
    Core/User/sys/sys_protocol.c
    Core/User/sys/sys_display.c
    Core/User/sys/sys_measure.c
    Core/User/sys/sys_time.c
    Core/User/sys/sys_button.c
    Core/User/sys/sys_storage.c
    Core/User/sys/sys_manage.c
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    Core/User/bsp
    Core/User/drv
    Core/User/middleware
    Core/User/sys
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
