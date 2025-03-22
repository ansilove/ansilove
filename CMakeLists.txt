cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

project(ansilove C)

include(CheckFunctionExists)
include(GNUInstallDirs)

# Conditional build options
set(ENABLE_SECCOMP 0 CACHE BOOL "Enable building with seccomp")

# Check if system has pledge and strtonum
list(APPEND CMAKE_REQUIRED_DEFINITIONS -D_OPENBSD_SOURCE)
check_function_exists(pledge HAVE_PLEDGE)
check_function_exists(strtonum HAVE_STRTONUM)

if(ENABLE_SECCOMP)
  # Check if system has seccomp
  message(STATUS "Looking for seccomp")
  find_path(SECCOMP NAMES "linux/seccomp.h")
  if(SECCOMP)
    message(STATUS "Looking for seccomp - found")
    add_definitions(-DHAVE_SECCOMP)
  else()
    message(STATUS "Looking for seccomp - not found")
  endif()
endif(ENABLE_SECCOMP)

# Additional include directories for compat functions
include_directories("compat")

# Ansilove library
find_path(ANSILOVE_INCLUDE_DIRS ansilove.h)
find_library(ANSILOVE_LIBRARIES NAMES ansilove REQUIRED)
include_directories(${ANSILOVE_INCLUDE_DIRS})

set(SRC src/ansilove.c src/types.c src/strtolower.c src/sauce.c)

if(NOT HAVE_PLEDGE)
  set(SRC ${SRC} compat/pledge.c)
endif()

if(NOT HAVE_STRTONUM)
  set(SRC ${SRC} compat/strtonum.c)
endif()

add_definitions(-D_GNU_SOURCE -Wall -Wextra -pedantic)
add_executable(ansilove ${SRC})

target_link_libraries(ansilove ${ANSILOVE_LIBRARIES})

install(TARGETS ansilove DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES man/ansilove.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1/)

enable_testing()
add_test(ansilove ansilove)
add_test(ansi ansilove ${PROJECT_SOURCE_DIR}/tests/bs-alove.ans)
add_test(artworx ansilove ${PROJECT_SOURCE_DIR}/tests/bs-alove.adf)
add_test(bin ansilove -c 80 ${PROJECT_SOURCE_DIR}/tests/bs-alove.bin)
add_test(pcboard ansilove ${PROJECT_SOURCE_DIR}/tests/bs-alove.pcb)
add_test(tundra ansilove ${PROJECT_SOURCE_DIR}/tests/bs-alove.tnd)
add_test(xbin ansilove ${PROJECT_SOURCE_DIR}/tests/bs-alove.xb)
add_test(retina ansilove -r ${PROJECT_SOURCE_DIR}/tests/bs-alove.ans)
add_test(sauce ansilove -s ${PROJECT_SOURCE_DIR}/tests/sauce.txt)
