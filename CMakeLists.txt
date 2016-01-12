cmake_minimum_required (VERSION 2.6)

project (ansilove C)

include(CheckFunctionExists)
include_directories(/usr/local/include /usr/pkg/include)
include(GNUInstallDirs)

check_function_exists(strtonum HAVE_STRTONUM)

find_library(LIB_GD NAMES gd REQUIRED)

set (SRC src/main.c src/albinfonts.c src/ansilove.c src/explode.c src/filesize.c src/strtolower.c src/substr.c)

if(NOT HAVE_STRTONUM)
  set (SRC ${SRC} compat/strtonum.c)
endif()

add_definitions(-Wall -Wextra -Werror -std=gnu99 -pedantic)
add_executable(ansilove ${SRC})

target_link_libraries(ansilove ${LIB_GD} m)

install(TARGETS ansilove DESTINATION bin)
install(FILES ansilove.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1/)
