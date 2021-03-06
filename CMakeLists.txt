cmake_minimum_required(VERSION 3.16)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/arm-none-eabi-gcc.cmake")
endif()

project(drone_software)

enable_language(C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

aux_source_directory(software/app/src                                                   SOURCE)
aux_source_directory(software/StdPeriph_Driver/src                                      SOURCE)
aux_source_directory(software/Third_Party/FreeRTOS/org/Source                           SOURCE)
aux_source_directory(software/Third_Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F     SOURCE)
aux_source_directory(software/Third_Party/FreeRTOS/org/Source/portable/MemMang          SOURCE)

set(SOURCE "${SOURCE};software/startup/startup_stm32.s")

set(EXECUTABLE ${PROJECT_NAME}.elf)

add_executable(${EXECUTABLE} ${SOURCE})

target_compile_definitions(${EXECUTABLE} PRIVATE
        -DSTM32F40_41xxx
        -DUSE_STDPERIPH_DRIVER
        )

target_include_directories(${EXECUTABLE} PRIVATE
        software/app/inc
        software/CMSIS/core
        software/CMSIS/device
        software/StdPeriph_Driver/inc
        software/Third_Party/FreeRTOS/org/Source/include
        software/Third_Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F
        )

target_compile_options(${EXECUTABLE} PRIVATE
        -mcpu=cortex-m4
        -mthumb
        -mfloat-abi=hard
        -mfpu=fpv4-sp-d16
        -fdata-sections
        -ffunction-sections
        -Wall

        $<$<CONFIG:Debug>:-Og>
        $<$<CONFIG:Debug>:-g>

        $<$<CONFIG:Release>:-Os>
        $<$<CONFIG:Release>:-flto>

        $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
        $<$<COMPILE_LANGUAGE:CXX>:-Wuseless-cast>
        $<$<COMPILE_LANGUAGE:CXX>:-Wsuggest-override>
        $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
        $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
        $<$<COMPILE_LANGUAGE:CXX>:-D_Static_assert=static_assert>
        )
target_link_options(${EXECUTABLE} PRIVATE
        -T${CMAKE_SOURCE_DIR}/software/LinkerScript.ld
        -mcpu=cortex-m4
        -mthumb
        -mfloat-abi=hard
        -mfpu=fpv4-sp-d16
        -specs=nosys.specs
        -lc
        -lm
        -lnosys
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -Wl,--gc-sections,--print-memory-usage
        )

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND arm-none-eabi-size ${EXECUTABLE})

# Create hex file
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND arm-none-eabi-objcopy -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
        COMMAND arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin)

# Improve clean target
set_target_properties(${EXECUTABLE} PROPERTIES ADDITIONAL_CLEAN_FILES
        "${PROJECT_NAME}.bin;${PROJECT_NAME}.hex;${PROJECT_NAME}.map")