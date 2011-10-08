cmake_minimum_required (VERSION 2.6)
project (pedalog-tool)

add_executable(pedalog-tool src/pedalog-tool.c)
target_link_libraries(pedalog-tool pedalog)

# The version number.
set (PEDALOG_TOOL_VERSION_MAJOR 0)
set (PEDALOG_TOOL_VERSION_MINOR 4)

install (TARGETS pedalog-tool DESTINATION bin)

# Create 'dist' target to build source tarball
set(PROJECT_VERSION "${PEDALOG_TOOL_VERSION_MAJOR}.${PEDALOG_TOOL_VERSION_MINOR}")
set(ARCHIVE_NAME ${CMAKE_PROJECT_NAME}-${PROJECT_VERSION})
add_custom_target(dist
    COMMAND git archive --prefix=${ARCHIVE_NAME}/ HEAD
        | gzip > ${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar.gz
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
