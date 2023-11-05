file(GLOB SOURCES Source/*.cpp)
add_library(Detour3D ${SOURCES})

add_library(RecastNavigation::Detour3D ALIAS Detour3D)
set_target_properties(Detour3D PROPERTIES DEBUG_POSTFIX -d)

set(Detour3D_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include")

if(RECASTNAVIGATION_DT_POLYREF64)
    target_compile_definitions(Detour3D PUBLIC DT_POLYREF64)
endif()

if(RECASTNAVIGATION_DT_VIRTUAL_QUERYFILTER)
    target_compile_definitions(Detour3D PUBLIC DT_VIRTUAL_QUERYFILTER)
endif()

target_include_directories(Detour3D PUBLIC
    "$<BUILD_INTERFACE:${Detour_INCLUDE_DIR}>"
)

# Include Detour for Common Utils to work with the library better.
target_link_libraries(Detour3D PUBLIC Detour)
target_include_directories(Detour3D PUBLIC "${CMAKE_SOURCE_DIR}/Detour/Include")

set_target_properties(Detour3D PROPERTIES
    SOVERSION ${SOVERSION}
    VERSION ${LIB_VERSION}
    COMPILE_PDB_OUTPUT_DIRECTORY .
    COMPILE_PDB_NAME "Detour3D-d"
)

install(TARGETS Detour3D
    EXPORT recastnavigation-targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT library
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} ${CMAKE_INSTALL_INCLUDEDIR}/recastnavigation
)

file(GLOB INCLUDES Include/*.h)
install(FILES ${INCLUDES} DESTINATION
    ${CMAKE_INSTALL_INCLUDEDIR}/recastnavigation)

if(MSVC)
    install(FILES "$<TARGET_FILE_DIR:Detour>/Detour3D-d.pdb" CONFIGURATIONS "Debug" DESTINATION "lib" OPTIONAL)
endif()
