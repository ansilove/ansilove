```
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
```

# AnsiLove/C

[![Build Status][1]][2]

This is a complete rewrite of [AnsiLove/PHP][3] in the C programming
language. It converts ANSi and artscene related file formats into
PNG images. The project is considered as stable, current version
is `4.0.7`.

# Specs

AnsiLove/C is strictly using the `C99 standard` to achieve high
portability to all major operating systems. Supported compilers are
`GCC` and `Clang`, others may work but aren't tested. We use Linux
and OpenBSD for AnsiLove/C development.

# Why C?

There were many reasons, most notably PHP interpreter independence
and performance. A solid C foundation is just perfect for creating
libraries and it can easily be embedded into applications. We already
mentioned portability. What else? We wanted evolution. AnsiLove/C
should not be understood as a port. It takes many different approaches
(like processing binary font dumps or generating @2x Retina images),
it is overall improved and introduces new features. While results
tend to be the same, the codebase does not have much in common with
it's ancestor.

# Dependencies

AnsiLove/C uses the `CMake` build system and requires the
[libansilove][4] library and header files.

# Installing dependencies

- OpenBSD: `pkg_add -r cmake`
- NetBSD: `pkgin install cmake`
- FreeBSD: `pkg install cmake`
- Mac OS X: `brew install cmake`
- Alpine Linux: `apk add cmake gcc make musl-dev`
- Debian / Ubuntu / Mint: `apt-get install cmake`
- Solus: `eopkg install -c system.devel`

For now, `libansilove` has to be installed manually.

# Compiling

	mkdir build
	cd build
	cmake ..
	make

# Installation

AnsiLove/C packages are available for:

### OpenBSD

	pkg_add ansilove

### Pkgsrc (NetBSD, SmartOS, Mac OS X, etc.)

	pkgin install ansilove

### FreeBSD

	pkg install ansilove

### Debian / Ubuntu

	apt install ansilove

### Solus

	eopkg install ansilove

# Features

The following formats are supported:

- .ANS - ANSi (ANSI escape sequences: ANSI X3.64 standard)
- .PCB - PCBoard Bulletin Board System (BBS) own file format
- .BIN - Binary format (raw memory copy of text mode video memory)
- .ADF - Artworx format, supporting custom character sets and palettes
- .IDF - iCE Draw format, supporting custom character sets and palettes
- .TND - [TundraDraw][5] format, supporting 24-bit color mode
- .XB - The eXtended Binary [XBin][6] format, supporting custom character sets
  and palettes

Files with custom suffix default to the ANSi renderer (e.g. ICE or CIA).

AnsiLove/C is capabable of processing:

- [SAUCE][7] records
- DOS and Amiga fonts (embedded binary dump)
- iCE colors

Even more:

- Output files are highly optimized 4-bit PNGs.
- Optionally generates proper Retina @2x (and up to @8x) PNG.
- You can use custom options for adjusting output results.
- Built-in support for rendering Amiga ASCII.

# Documentation

## Synopsis

```
     ansilove [-dhiqrsv] [-b bits] [-c columns] [-f font] [-m mode] [-o file]
              [-R factor] file
```

## Options

```
     -b bits     Set to 9 to render 9th column of block characters (default:
                 8).

     -c columns  Adjust number of columns for ANSI, BIN, and TND files.

     -d          Enable DOS aspect ratio.

     -f font     Select font for supported formats.

     -h          Show help.

     -i          Enable iCE colors.

     -m mode     Set rendering mode for ANS files. Valid options are:

                 ced     Black on gray, with 78 columns.

                 transparent
                         Render with transparent background.

                 workbench
                         Use Amiga Workbench palette.

     -o file     Specify output filename/path.

     -q          Suppress output messages (quiet).

     -r          Create Retina @2x output file.

     -R factor   Create Retina output file with custom scale factor.

     -s          Show SAUCE record without generating output.

     -v          Show version information.
```

There are certain cases where you need to set options for proper
rendering. However, this is occasionally. Results turn out well
with the built-in defaults.

## Fonts

We dumped many fonts as binary data right into AnsiLove/C, so the
most popular typefaces for rendering ANSi / ASCII art are available
at your fingertips.

PC fonts can be (all case-sensitive):

- `80x25` Default (Code page 437)
- `80x50` 80x50 mode (Code page 437)
- `cp737` Greek (Code page 737)
- `cp775` Baltic (Code page 775)
- `cp850` Latin-1 (Code page 850)
- `cp852` Latin-2 (Code page 852)
- `cp855` Cyrillic (Code page 855)
- `cp857` Turkish (Code page 857)
- `cp860` Portuguese (Code page 860)
- `cp861` Icelandic (Code page 861)
- `cp862` Hebrew (Code page 862)
- `cp863` French Canadian (Code page 863)
- `cp865` Nordic (Code page 865)
- `cp866` Russian (Code page 866)
- `cp869` Greek (Code page 869)
- `terminus` Terminus (Modern font, code page 437)

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

`bits` can be:

- `8` (8-bit)
- `9` (9-bit)

Setting the bits to `9` will render the 9th column of block characters,
so the output will look like it is displayed in real textmode.

## Rendering Mode

`mode` can be (all case-sensitive):

- `ced`
- `transparent`
- `workbench`

Setting the mode to `ced` will cause the input file to be rendered
in black on gray, and limit the output to 78 columns (only available
for `ANS` files). Used together with an Amiga font, the output will
look like it is displayed on Amiga.

Setting the mode to `workbench` will cause the input file to be
rendered using Amiga Workbench colors (only available for `ANS`
files).

Settings the mode to `transparent` will produce output files with
transparent background (only available for `ANS` files).

## iCE Colors

iCE colors are disabled by default, and can be enabled by specifying
the `-i` option.

When an ANSi source was created using iCE colors, it was done with
a special mode where the blinking was disabled, and you had 16
background colors available. Basically, you had the same choice for
background colors as for foreground colors, that's iCE colors.

## Columns

`columns` is only relevant for .ANS, .BIN, and .TND files, and is
optional. In most cases conversion will work fine if you don't set
this flag, the default value is `160` for .BIN files and `80`
otherwise.

## SAUCE records

It's fine to use AnsiLove/C as SAUCE reader without generating any
output, just set option `-s` for this purpose.

# License

AnsiLove/C is released under the BSD 2-Clause License. See the
`LICENSE` file for details.

# Authors

AnsiLove/C is developed by Stefan Vogt ([@ByteProject][8]), Brian Cassidy
([@bricas][9]) and Frederic Cambus ([@fcambus][10]).

# Resources

Project homepage: https://www.ansilove.org

GitHub: https://github.com/ansilove/ansilove

[1]: https://api.travis-ci.org/ansilove/ansilove.png?branch=master
[2]: https://travis-ci.org/ansilove/ansilove
[3]: https://www.ansilove.org
[4]: https://github.com/ansilove/libansilove
[5]: https://sourceforge.net/projects/tundradraw/
[6]: https://github.com/radman1/xbin
[7]: https://github.com/radman1/sauce
[8]: https://github.com/ByteProject
[9]: https://github.com/bricas
[10]: https://github.com/fcambus
