cmake_minimum_required(VERSION 3.20)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(CMAKE_SYSTEM_VERSION 1)

set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(lab5 C CXX ASM)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_definitions(-DDEBUG)

add_compile_options(-mcpu=cortex-m0plus -mthumb)
add_compile_options(-Wall -fomit-frame-pointer -g)

# Corrected linker options
add_link_options(-Wl,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-T${CMAKE_SOURCE_DIR}/stm32.ld)
add_link_options(--specs=nosys.specs -nostdlib)

# Corrected executable build
add_executable(${PROJECT_NAME}.elf main.c startup.s)

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(
        TARGET ${PROJECT_NAME}.elf
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Building ${HEX_FILE}"
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_COMMAND} -E echo "Building ${BIN_FILE}"
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMAND ${CMAKE_OBJDUMP} -D $<TARGET_FILE:${PROJECT_NAME}.elf> -j.text --disassembler-color=extended
        VERBATIM
)

set_property(
        TARGET ${PROJECT_NAME}.elf
        APPEND PROPERTY ADDITIONAL_CLEAN_FILES
        ${PROJECT_NAME}.map ${PROJECT_NAME}.bin ${PROJECT_NAME}.hex
)
