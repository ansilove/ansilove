# AnsiLove/C

This is a complete rewrite of [AnsiLove/PHP](http://ansilove.sourceforge.net) in the C programming language. It converts ANSi and artscene related file formats into [PNG images](http://cl.ly/1D0o1M2t2Y190v33462F/o). Unlike the PHP variant, AnsiLove/C is intended as UNIX command line tool you install preferably to `/usr/bin`. The project is considered as completed and stable, current version is `2.1.0`.

# Specs 

AnsiLove/C is strictly using the `C99 standard` to achieve high portability to all major operating systems. It's developed from ground up with the vision to compile just fine on your platform. Be sure to link against `libgd` when compiling which is also needed when running the binary. Supported compilers are `GCC` and `Clang`, others may work but aren't tested. All files include the C standard headers. An exception is compilation on `Mac OS X`, where defines in the sources ensure importing `<Foundation/Foundation.h>`. In other words: on the Mac, the resulting binary is a Foundation tool. We use Mac OS X and Linux for AnsiLove/C development. You'll find a Xcode project file in this repository. Additional there's a shell script that builds AnsiLove/C on Ubuntu, it should compile on other distros as well. Feel free to fork and add custom build scripts for your own platform, [Homebrew](https://github.com/mxcl/homebrew) formulas, Linux packages, whatever.

# Why C?

There were many reasons, most notably PHP interpreter independence and performance. A solid C foundation is just perfect for creating libraries and frameworks and it can easily embedded into applications. We already mentioned portability. What else? We wanted evolution. AnsiLove/C should not be understood as a port. It takes many different approaches (like processing binary font dumps or generating @2x Retina images), it is overall improved and introduces new features. While results tend to be the same, the codebase does not have much in common  with it's ancestor. 

# Cocoa developers

If you're looking for something to implement into your Cocoa applications, we highly recommend taking a look at [AnsiLove.framework](https://github.com/ByteProject/AnsiLove.framework), which is actively maintained by [@ByteProject](https://github.com/ByteProject) and always based on the latest AnsiLove/C sources.

# Build script for Ubuntu

Use `shbuild/build_ubuntu.sh` to build AnsiLove/C on Ubuntu. Will probably work on other distros as well. 

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
- You can use custom operands for adjusting output results.
- Built-in support for rendering Amiga ASCII.

# Documentation

One major goal for AnsiLove/C was implementing the look and feel of common UNIX command line tools. We strictly follow the `IEEE Std 1003.1` for utility conventions while maintaining compabtiblity with `GNU`. Users comfortable with either one or the other standard should feel home.

## Synopsis

	ansilove file -i [operands]
	ansilove file -ir [operands]
	ansilove file -o output [operands]
	ansilove file -or output [operands]
	ansilove file -s
	ansilove -vhe

## Options

	-i   output identical to input with .png suffix added
	-ir  same as -i, creates additional Retina @2x output file
	-o   specify custom file name / path for output
	-or  same as -o, creates additional Retina @2x output file
	-s   display SAUCE record without generating output
	-v   version information, equivalent to --version
	-h   show help, equivalent to --help
	-e   print a list of examples

Hint: Don't add .png suffix when specifying a custom path/name for output as it will be added automatically.

## Operands

	font bits icecolors columns

Optional values to adjust output. There are certain cases where you need to set operands for proper rendering. However, this is occassionally. Results turn out well with the built-in defaults. You may launch AnsiLove with the option `-e` to get a list of basic examples, with and without operands. Note that columns is restricted to `BIN` files, it won't affect other file types. It's also worth mentioning that setting a certain operand requires to set all operands before, so if you need to modifiy the `icecolors` operand, you have to set `font` and `bits` as well. On the other hand, it's fine to set the `font` operand while not setting any of the following. Got that?

## font (operand)

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

## bits (operand)

`bits` can be (all case-sensitive): 

- `8` (8-bit)
- `9` (9-bit)
- `ced`
- `transparent`
- `workbench`

Setting the bits to `9` will render the 9th column of block characters, so the output will look like it is displayed in real textmode. 

Setting the bits to `ced` will cause the input file to be rendered in black on gray, and limit the output to 78 columns (only available for `ANS` files). Used together with an `AMIGA` font, the output will look like it is displayed on Amiga.

Setting the bits to `workbench` will cause the input file to be rendered using Amiga Workbench colors (only available for `ANS` files).

Settings the bits to `transparent` will produce output files with transparent background (only available for `ANS` files).

## icecolors (operand)

`icecolors` can be:

- `0`
- `1`

Setting `icecolors` to `1` will enable iCE color codes. On the opposite `0` means that that `icecolors` are disabled, which is the default value. When an ANSi source was created using iCE colors, it was done with a special mode where the blinking was disabled, and you had 16 background colors available. Basically, you had the same choice for background colors as for foreground colors, that's iCE colors. But now the important part: when the ANSi source does not make specific use of iCE colors, you should NOT set this flag. The file could look pretty weird in normal mode. So in most cases it's fine to turn iCE colors off. 

## columns (operand)

`columns` is only relevant for ANSi source files with `BIN` extension and even for those files optional. In most cases conversion will work fine if you don't set this flag, the default value is `160` then. So please pass `columns` only to `BIN` files and only if you exactly know what you're doing. A KITTEN MAY DIE SOMEWHERE.

## SAUCE records

It's fine to use AnsiLove/C as SAUCE reader without generating any output, just set option `-s` for this purpose. 

# Who pulls the strings

AnsiLove/C is developed by Stefan Vogt ([@ByteProject](https://github.com/ByteProject)), Brian Cassidy ([@bricas](https://github.com/bricas)) and Frederic Cambus ([@fcambus](https://github.com/fcambus)).

# License

AnsiLove/C is released under a MIT-style license. See the file `LICENSE` for details.
