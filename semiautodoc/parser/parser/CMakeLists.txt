cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# ---------------- Paths ----------------
set( ROOT ${CMAKE_CURRENT_SOURCE_DIR}/.. )

# ---------------- Main project properties ----------------

project(parser CXX C)

# ---------------- Sources ----------------

set( SOURCES_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/src )
set( INCLUDES_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/include )

set( parser_SOURCES
    ${INCLUDES_ROOT}/element.hpp
    ${INCLUDES_ROOT}/class.hpp
    ${INCLUDES_ROOT}/function.hpp
    ${INCLUDES_ROOT}/parser.hpp

    ${SOURCES_ROOT}/element.cpp
    ${SOURCES_ROOT}/class.cpp
    ${SOURCES_ROOT}/function.cpp
    ${SOURCES_ROOT}/parser.cpp
)

# ---------------- Targets ----------------
add_library( parser ${parser_SOURCES} )
set_property( TARGET parser PROPERTY CXX_STANDARD 17 )

target_include_directories(parser PUBLIC ${INCLUDES_ROOT})
