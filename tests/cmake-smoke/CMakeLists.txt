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
target_include_directories(nsx_core INTERFACE ${CMAKE_CURRENT_LIST_DIR}/stub)

# Placement case: sram_bss, tcm, or m55.
set(NSX_SMOKE_CASE sram_bss CACHE STRING "RTT placement case under test")
if(NSX_SMOKE_CASE STREQUAL "sram_bss")
    target_compile_definitions(nsx_core INTERFACE NSX_SMOKE_SRAM_BSS)
    set(NSX_SMOKE_WANT .sram_bss)
elseif(NSX_SMOKE_CASE STREQUAL "tcm")
    set(NSX_SMOKE_WANT .bss)
elseif(NSX_SMOKE_CASE STREQUAL "m55")
    target_compile_definitions(nsx_core INTERFACE NSX_SMOKE_SRAM_BSS AM_PART_APOLLO510)
    set(NSX_SMOKE_WANT .bss)
else()
    message(FATAL_ERROR "Unknown NSX_SMOKE_CASE: ${NSX_SMOKE_CASE}")
endif()

get_filename_component(NSX_SEGGER_RTT_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
add_subdirectory("${NSX_SEGGER_RTT_SOURCE_DIR}" nsx-segger-rtt)

add_executable(cmake_link_smoke main.c)
target_link_libraries(cmake_link_smoke PRIVATE nsx::segger_rtt)

enable_testing()
add_test(NAME rtt_section
    COMMAND ${CMAKE_CURRENT_LIST_DIR}/check-section.sh $<TARGET_FILE:cmake_link_smoke> ${NSX_SMOKE_WANT})
