# AnsiLove/C

This is a complete rewrite of [AnsiLove/PHP](http://ansilove.sourceforge.net) in the C programming language. It converts ANSi and artscene related file formats into PNG images. Unlike the PHP variant, AnsiLove/C is intended as UNIX command line tool you install preferably to /usr/bin. Right now the project is in an early stage of development. It's neither considered as finished nor as stable product, but we are busy working on it.

# Specs 

AnsiLove/C is strictly using the `C99 standard` to achieve high portability to all major operating systems. It's developed from ground up with the vision to compile just fine on your platform. Be sure to link against `libgd` when compiling which is also needed when running the binary. Supported compilers are `gcc` and `Clang`, others may work but aren't tested. All files include the C standard headers. An exception is compilation on `Mac OS X`, where defines in the sources ensure importing `<Foundation/Foundation.h>`. In other words: the resulting binary on the Mac is a Foundation tool. We use Mac OS X and Linux for AnsiLove/C development. You'll find a Xcode project file in this repository. Additional there's a shell script that builds AnsiLove/C on Ubuntu, it should compile on other distros as well.

# Why porting to C?

There are many reasons for doing this, most notably PHP interpreter independence and performance. A solid C foundation is just perfect for creating libraries and frameworks and it can easily embedded into applications. We already mentioned portability: while there isn't a PHP CLI available for every system, there are very few computer architectures for which a C compiler does not exist. What else? We want evolution. In certain situations, PHP is pretty limited. So AnsiLove/C is not an one to one porting of it's ancestor, it's overall improved and introduces new features.

# Cocoa / Foundation bridge

If you're looking for something to implement into your Cocoa or Foundation applications, we highly recommend taking a look at [@ByteProject's](https://github.com/ByteProject) [AnsiLove.framework](https://github.com/ByteProject/AnsiLove.framework), which actively maintained and runninng smooth and stable. It uses a modfied version of [AnsiLove/PHP](http://ansilove.sourceforge.net) as rendering library and provides a Cocoa layer on top of it.  Once AnsiLove/C is finished, it will replace [AnsiLove/PHP](http://ansilove.sourceforge.net) in the [AnsiLove.framework](https://github.com/ByteProject/AnsiLove.framework), to go all the way native.

# Who pulls the strings

AnsiLove/C is developed by Stefan Vogt ([@ByteProject](https://github.com/ByteProject)), Brian Cassidy ([@bricas](https://github.com/bricas)) and Frederic Cambus ([@fcambus](https://github.com/fcambus)) also known as `the international ANSi conspiracy".

# License

AnsiLove/C is released under a MIT-style license. See the file `LICENSE` for details.
