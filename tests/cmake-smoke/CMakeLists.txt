cmake_minimum_required(VERSION 3.20)

# Cross-compile with arm-none-eabi-gcc.
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(nsx_segger_rtt_smoke C)
include(GNUInstallDirs)

set(NSX_SMOKE_ARCH -mthumb -mcpu=cortex-m4)
add_compile_options(${NSX_SMOKE_ARCH} -Wall)
add_link_options(${NSX_SMOKE_ARCH} --specs=nosys.specs)

add_library(nsx_cmsis_core INTERFACE)
add_library(nsx::cmsis_core ALIAS nsx_cmsis_core)
add_library(nsx_core INTERFACE)
add_library(nsx::core ALIAS nsx_core)

get_filename_component(NSX_SEGGER_RTT_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
add_subdirectory("${NSX_SEGGER_RTT_SOURCE_DIR}" nsx-segger-rtt)

add_executable(cmake_link_smoke main.c)
target_link_libraries(cmake_link_smoke PRIVATE nsx::segger_rtt)
