cmake_minimum_required (VERSION 2.6)
project (pedalog-tool)

add_executable(pedalog-tool src/pedalog-tool.c)
target_link_libraries(pedalog-tool pedalog)

# The version number.
set (PEDALOG_TOOL_VERSION_MAJOR 0)
set (PEDALOG_TOOL_VERSION_MINOR 2)

install (TARGETS pedalog-tool DESTINATION bin)
