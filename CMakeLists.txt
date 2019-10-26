cmake_minimum_required (VERSION 2.6)

project (ansilove C)

include(CheckFunctionExists)
include(GNUInstallDirs)

# Check if system has pledge and strtonum
list(APPEND CMAKE_REQUIRED_DEFINITIONS -D_OPENBSD_SOURCE)
check_function_exists(pledge HAVE_PLEDGE)
check_function_exists(strtonum HAVE_STRTONUM)

# Check if system has seccomp
message(STATUS "Looking for seccomp")
find_path(SECCOMP NAMES "linux/seccomp.h")
if(SECCOMP)
  message(STATUS "Looking for seccomp - found")
  add_definitions(-DHAVE_SECCOMP=1)
else()
  message(STATUS "Looking for seccomp - not found")
endif()

# Additional include directories for compat functions
include_directories("compat")

# Ansilove library
find_path(ANSILOVE_INCLUDE_DIRS ansilove.h)
find_library(ANSILOVE_LIBRARIES NAMES ansilove REQUIRED)
include_directories(${ANSILOVE_INCLUDE_DIRS})

set(SRC src/ansilove.c src/strtolower.c src/sauce.c)

if(NOT HAVE_PLEDGE)
  set (SRC ${SRC} compat/pledge.c)
endif()

if(NOT HAVE_STRTONUM)
  set (SRC ${SRC} compat/strtonum.c)
endif()

add_definitions(-Wall -Wextra -std=c99 -pedantic)
add_executable(ansilove ${SRC})

target_link_libraries(ansilove ${ANSILOVE_LIBRARIES} m)

install(TARGETS ansilove DESTINATION bin)
install(FILES ansilove.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1/)
