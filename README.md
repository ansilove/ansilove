	         _______         ___________          ___
	       __\___   \_  ____/     /\   /______ ___\_/__            /\
	      /    \|     \/  _ \    /--\_____    \\   /  /\          /  \
	    _/      |     /    \     \      |/     /      \ \ _ _____/    \_______
	    \       |_____\____/     /      /      \____  /\/                    /
	     \______|      \  \_____/\______       /\   \/  \   /\NSILOVE / C   /____ _
	      \     |_______\__\___ \ \    \      /  \___\__/____
	       \____|        /____/\_\/\__ /     / __/___ \     /\    ____
	                     \    \ \     /     /_/ __   \/    /__\__/  _/ _____ ___
	                 /\   \____\/    /     //   \    /    /    /    _>/    //__/\
	                /  \           _/      \   //   /    /    /     \/    / \__\/
	_ _________    /    \_______ _ \___    /_______/    /   _/ \____      \  /
	           \  /                 \ \___/\       \_______/\\  \  \______/\/
	            \/                   \_\  \ \_______\      \ \\/ \__\     \ \
	                                    \__\/        \______\/ h7/dS!\_____\/
	
# AnsiLove/C

This is a complete rewrite of [AnsiLove/PHP](http://ansilove.sourceforge.net) in the C programming language. It converts ANSi and artscene related file formats into [PNG images](http://cl.ly/1D0o1M2t2Y190v33462F/o). Unlike the PHP variant, AnsiLove/C is intended as UNIX command line tool you install preferably to `/usr/bin`. The project is considered as stable, current version is `2.2.1`.

# Specs 

AnsiLove/C is strictly using the `C99 standard` to achieve high portability to all major operating systems. It's developed from ground up with the vision to compile just fine on your platform. Supported compilers are `GCC` and `Clang`, others may work but aren't tested. We use Linux, OpenBSD and Mac OS X for AnsiLove/C development.

# Why C?

There were many reasons, most notably PHP interpreter independence and performance. A solid C foundation is just perfect for creating libraries and frameworks and it can easily embedded into applications. We already mentioned portability. What else? We wanted evolution. AnsiLove/C should not be understood as a port. It takes many different approaches (like processing binary font dumps or generating @2x Retina images), it is overall improved and introduces new features. While results tend to be the same, the codebase does not have much in common with it's ancestor.

# Dependencies

AnsiLove/C uses the `CMake` build system and requires the `GD` library and header files.

# Installing dependencies

- OpenBSD : pkg_add -r cmake gd
- NetBSD : pkgin install cmake gd
- Mac OS X : brew install cmake gd
- Alpine Linux : apk add cmake gcc make musl-dev gd-dev
- Debian / Ubuntu : apt-get install cmake libgd-dev

# Compiling

    cmake .
    make

# Cocoa

If you're looking for something to implement into your Cocoa applications, we highly recommend taking a look at [AnsiLove.framework](https://github.com/ByteProject/AnsiLove.framework).

# Features

Rendering of all known ANSi / ASCII art file types:

- ANSi (.ANS)
- Binary (.BIN)
- Artworx (.ADF)
- iCE Draw (.IDF)
- Xbin (.XB) [details](http://www.acid.org/info/xbin/xbin.htm)
- PCBoard (.PCB)
- Tundra (.TND) [details](http://sourceforge.net/projects/tundradraw)
- ASCII (.ASC)
- Release info (.NFO)
- Description in zipfile (.DIZ)

Files with custom suffix default to the ANSi renderer (e.g. ICE or CIA).

AnsiLove/C is capabable of processing: 

- SAUCE records
- DOS and Amiga fonts (embedded binary dump) 
- iCE colors

Even more:

- Output files are highly optimized 4-bit PNGs.
- Optionally generates additional (and proper) Retina @2x PNG.
- You can use custom options for adjusting output results.
- Built-in support for rendering Amiga ASCII.

# Documentation

## Synopsis

       ansilove [options] file
       ansilove -e | -h | -v

## Options

       -b bits     set to 9 to render 9th column of block characters (default: 8)
       -c columns  adjust number of columns for BIN files (default: 160)
       -e          print a list of examples
       -f font     select font (default: 80x25)
       -h          show help
       -i          enable iCE colors
       -m mode     set rendering mode for ANS files:
                     ced            black on gray, with 78 columns
                     transparent    render with transparent background
                     workbench      use Amiga Workbench palette
       -o file     specify output filename/path
       -r          creates additional Retina @2x output file
       -s          show SAUCE record without generating output
       -v          show version information

There are certain cases where you need to set options for proper rendering. However, this is occasionally. Results turn out well with the built-in defaults. You may launch AnsiLove with the option `-e` to get a list of basic examples. Note that columns is restricted to `BIN` files, it won't affect other file types.

## Fonts

We dumped many fonts as binary data right into AnsiLove/C, so the most popular typefaces for rendering ANSi / ASCII art are available at your fingertips. 

PC fonts can be (all case-sensitive):

- `80x25` (code page 437)
- `80x50` (code page 437, 80x50 mode)
- `baltic` (code page 775)
- `cyrillic` (code page 855)
- `french-canadian` (code page 863)
- `greek` (code page 737)
- `greek-869` (code page 869)
- `hebrew` (code page 862)
- `icelandic` (Code page 861)
- `latin1` (code page 850)
- `latin2` (code page 852)
- `nordic` (code page 865)
- `portuguese` (Code page 860)
- `russian` (code page 866)
- `terminus` (modern font, code page 437)
- `turkish` (code page 857)

AMIGA fonts can be (all case-sensitive):

- `amiga` (alias to Topaz)
- `microknight` (Original MicroKnight version)
- `microknight+` (Modified MicroKnight version)
- `mosoul` (Original mO'sOul font)
- `pot-noodle` (Original P0T-NOoDLE font)
- `topaz` (Original Topaz Kickstart 2.x version)
- `topaz+` (Modified Topaz Kickstart 2.x+ version)
- `topaz500` (Original Topaz Kickstart 1.x version)
- `topaz500+` (Modified Topaz Kickstart 1.x version)

## Bits

`bits` can be (all case-sensitive): 

- `8` (8-bit)
- `9` (9-bit)

Setting the bits to `9` will render the 9th column of block characters, so the output will look like it is displayed in real textmode.

## Rendering Mode

`mode` can be (all case-sensitive):

- `ced`
- `transparent`
- `workbench`

Setting the mode to `ced` will cause the input file to be rendered in black on gray, and limit the output to 78 columns (only available for `ANS` files). Used together with an Amiga font, the output will look like it is displayed on Amiga.

Setting the mode to `workbench` will cause the input file to be rendered using Amiga Workbench colors (only available for `ANS` files).

Settings the mode to `transparent` will produce output files with transparent background (only available for `ANS` files).

## iCE Colors

iCE colors are disabled by default, and can be enabled by specifying the `-i` option.

When an ANSi source was created using iCE colors, it was done with a special mode where the blinking was disabled, and you had 16 background colors available. Basically, you had the same choice for background colors as for foreground colors, that's iCE colors.

## Columns

`columns` is only relevant for .BIN files, and even for those files is optional. In most cases conversion will work fine if you don't set this flag, the default value is `160` then. So please pass `columns` only to `BIN` files and only if you exactly know what you're doing.

## SAUCE records

It's fine to use AnsiLove/C as SAUCE reader without generating any output, just set option `-s` for this purpose. 

# Who pulls the strings

AnsiLove/C is developed by Stefan Vogt ([@ByteProject](https://github.com/ByteProject)), Brian Cassidy ([@bricas](https://github.com/bricas)) and Frederic Cambus ([@fcambus](https://github.com/fcambus)).

# License

AnsiLove/C is released under the BSD 3-Clause License. See the file `LICENSE` for details.
