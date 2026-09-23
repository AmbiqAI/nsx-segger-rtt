if(NOT TARGET nsx::core)
    message(FATAL_ERROR "nsx::core must be defined before nsx-segger-rtt is added.")
endif()

# Channel 0 buffers are compile-time sized.
set(NSX_SEGGER_RTT_BUFFER_SIZE_UP 1024 CACHE STRING "RTT channel 0 up buffer bytes")
set(NSX_SEGGER_RTT_BUFFER_SIZE_DOWN 16 CACHE STRING "RTT channel 0 down buffer bytes")

add_library(nsx_segger_rtt STATIC
    ${CMAKE_CURRENT_LIST_DIR}/RTT/SEGGER_RTT.c
)
set_target_properties(nsx_segger_rtt PROPERTIES EXPORT_NAME segger_rtt)
add_library(nsx::segger_rtt ALIAS nsx_segger_rtt)

target_link_libraries(nsx_segger_rtt PUBLIC
    nsx::cmsis_core
    nsx::core
)

target_compile_definitions(nsx_segger_rtt PUBLIC
    BUFFER_SIZE_UP=${NSX_SEGGER_RTT_BUFFER_SIZE_UP}
    BUFFER_SIZE_DOWN=${NSX_SEGGER_RTT_BUFFER_SIZE_DOWN}
)

target_include_directories(nsx_segger_rtt PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/RTT>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/Config>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/nsx/modules/nsx-segger-rtt/RTT>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/nsx/modules/nsx-segger-rtt/Config>
)

install(DIRECTORY
    ${CMAKE_CURRENT_LIST_DIR}/RTT
    ${CMAKE_CURRENT_LIST_DIR}/Config
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nsx/modules/nsx-segger-rtt
    FILES_MATCHING PATTERN "*.h"
)
install(TARGETS nsx_segger_rtt EXPORT nsxTargets)
