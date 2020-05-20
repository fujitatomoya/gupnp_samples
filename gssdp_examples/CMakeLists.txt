cmake_minimum_required(VERSION 3.1.0)

# project name is required
project(gssdp_examples C)

# get pkgconfig
find_package(PkgConfig REQUIRED)

# glib-2.0 required
pkg_check_modules(GLIB REQUIRED glib-2.0)
include_directories(${GLIB_INCLUDE_DIRS})
#message(STATUS ${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})
#message(STATUS ${GLIB_LIBRARY_DIRS})

# gssdp-1.0 required
pkg_check_modules(GSSDP REQUIRED gssdp-1.0)
include_directories(${GSSDP_INCLUDE_DIRS})
#message(STATUS ${GSSDP_INCLUDE_DIRS})
link_directories(${GSSDP_LIBRARY_DIRS})
#message(STATUS ${GSSDP_LIBRARY_DIRS})

# gobject-2.0 required
pkg_check_modules(GOBJECT REQUIRED gobject-2.0)
include_directories(${GOBJECT_INCLUDE_DIRS})
#message(STATUS ${GOBJECT_INCLUDE_DIRS})
link_directories(${GOBJECT_LIBRARY_DIRS})
#message(STATUS ${GOBJECT_LIBRARY_DIRS})

# Publisher Example
add_executable (publisher publish.c)
target_link_libraries(publisher ${GLIB_LIBRARIES} ${GSSDP_LIBRARIES} ${GOBJECT_LIBRARIES})

# Browser Example
add_executable (browser browser.c)
target_link_libraries(browser ${GLIB_LIBRARIES} ${GSSDP_LIBRARIES} ${GOBJECT_LIBRARIES})
