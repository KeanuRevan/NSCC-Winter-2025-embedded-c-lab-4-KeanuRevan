cmake_minimum_required(VERSION 3.30)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(CMAKE_SYSTEM_VERSION 1)

set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(lab4 C CXX ASM)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

add_definitions(-DDEBUG)

add_compile_options(-mcpu=cortex-m0plus -mthumb)
add_compile_options(-Wall -fomit-frame-pointer)

add_link_options(-T${CMAKE_SOURCE_DIR}/stm32.ld)
add_link_options(--specs=nosys.specs -nostdlib)

add_executable(lab4.elf main.c startup.s stm32.ld)
