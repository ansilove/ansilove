cmake_minimum_required (VERSION 2.6)
project (ansilovec C)

find_library(LIB_ZLIB NAMES z REQUIRED)
find_library(LIB_JPEG NAMES jpeg REQUIRED)
find_library(LIB_PNG NAMES png REQUIRED)
find_library(LIB_FREETYPE freetype REQUIRED)
find_library(LIB_GD NAMES gd REQUIRED)

add_executable(ansilovec ansilove/main.c ansilove/albinfonts.c ansilove/ansilove.c ansilove/explode.c ansilove/filesize.c ansilove/strtolower.c ansilove/substr.c)

target_link_libraries(ansilovec ${LIB_ZLIB} ${LIB_JPEG} ${LIB_PNG} ${LIB_FREETYPE} ${LIB_GD})
