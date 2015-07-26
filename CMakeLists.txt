cmake_minimum_required (VERSION 2.6)
project (ansilove C)

find_library(LIB_GD NAMES gd REQUIRED)
include_directories(/usr/local/include)

add_definitions(-Wall -Wextra -std=c99 -pedantic)

add_executable(ansilove src/main.c src/albinfonts.c src/ansilove.c src/explode.c src/filesize.c src/strtolower.c src/substr.c)

target_link_libraries(ansilove ${LIB_GD} m)
