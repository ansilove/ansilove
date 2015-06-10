cmake_minimum_required (VERSION 2.6)
project (ansilove C)

find_library(LIB_ZLIB NAMES z REQUIRED)
find_library(LIB_JPEG NAMES jpeg REQUIRED)
find_library(LIB_PNG NAMES png REQUIRED)
find_library(LIB_FREETYPE freetype REQUIRED)
find_library(LIB_GD NAMES gd REQUIRED)

add_executable(ansilove src/main.c src/albinfonts.c src/ansilove.c src/explode.c src/filesize.c src/strtolower.c src/substr.c)

target_link_libraries(ansilove ${LIB_ZLIB} ${LIB_JPEG} ${LIB_PNG} ${LIB_FREETYPE} ${LIB_GD})
