cmake_minimum_required (VERSION 2.6)

project (ansilove C)

include(CheckFunctionExists)
include(GNUInstallDirs)

# Check if system has pledge and strtonum
list(APPEND CMAKE_REQUIRED_DEFINITIONS -D_OPENBSD_SOURCE)
check_function_exists(pledge HAVE_PLEDGE)
check_function_exists(strtonum HAVE_STRTONUM)

# Additional include directories for compat functions
include_directories("compat")

# GD
find_path(GD_INCLUDE_DIRS gd.h)
find_library(GD_LIBRARIES NAMES gd REQUIRED)
include_directories(${GD_INCLUDE_DIRS})

set(SRC src/main.c src/albinfonts.c src/ansilove.c src/explode.c src/filesize.c src/strtolower.c src/substr.c src/sauce.c)

set(FORMATS src/ansi.c src/artworx.c src/binary.c src/icedraw.c src/pcboard.c src/tundra.c src/xbin.c)

if(NOT HAVE_PLEDGE)
  set (SRC ${SRC} compat/pledge.c)
endif()

if(NOT HAVE_STRTONUM)
  set (SRC ${SRC} compat/strtonum.c)
endif()

add_definitions(-Wall -Wextra -Werror -std=gnu99 -pedantic)
add_executable(ansilove ${SRC} ${FORMATS})

target_link_libraries(ansilove ${GD_LIBRARIES} m)

install(TARGETS ansilove DESTINATION bin)
install(FILES ansilove.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1/)
