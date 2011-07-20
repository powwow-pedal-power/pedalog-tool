cmake_minimum_required (VERSION 2.6)
project (pedalog-tool)

add_executable(pedalog-tool src/pedalog-tool.c)
target_link_libraries(pedalog-tool pedalog)

# The version number.
set (PEDALOG_TOOL_VERSION_MAJOR 0)
set (PEDALOG_TOOL_VERSION_MINOR 1)

install (TARGETS pedalog-tool DESTINATION bin)

# Debian packaging
#set(CPACK_GENERATOR "DEB")
#set(CPACK_DEBIAN_PACKAGE_NAME "pedalog-tool")
#set(CPACK_DEBIAN_PACKAGE_DEPENDS "libpedalog (>=0.1)")
#set(CPACK_DEBIAN_PACKAGE_MAINTAINER "dan@powwow-pedal-power.org.uk")
#SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Command-line tool to read data from Pedalog devices")
#SET(CPACK_PACKAGE_VENDOR "PoWWow Pedal Power")
#SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
#SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
#SET(CPACK_PACKAGE_VERSION_MAJOR "0")
#SET(CPACK_PACKAGE_VERSION_MINOR "1")
#SET(CPACK_PACKAGE_VERSION_PATCH "0")
#INCLUDE(CPack)
