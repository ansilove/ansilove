# AnsiLove/C

This is a complete rewrite of [AnsiLove/PHP](http://ansilove.sourceforge.net) in the C programming language. It will convert ANSi and artscene related file formats into PNG images. Unlike it's PHP ancestor, AnsiLove/C is intended as UNIX command line tool you install preferably to /usr/bin. Right now the project is in an early stage of development and is neither considered as finished nor as stable product. 

# Specs 

AnsiLove/C is strictly using the `C99 standard` to achieve high portability to all major operating systems. It's developed from ground up with the vision to compile just fine on your platform. Be sure to link against `libgd` when compiling which is also needed when running the binary. Supported compilers are `gcc` and `Clang`, others may work but aren't tested. All files include to the C standard headers. An exception is compilation on `Mac OS X`, where defines in the sources ensure importing `<Foundation/Foundation.h>`. I for one develop AnsiLove/C on a Mac, you'll find a Xcode project file in this repository. 

# Why porting to C?

There are many reasons for doing this, most notably PHP interpreter independence and performance. A solid C foundation is also perfect for creating libraries or frameworks and it can easily embedded into applications. Webservers, able to execute C code and binaries would benefit form this port as well. 

# Cocoa / Foundation developers

If you're looking for something to implement into your Cocoa or Foundation applications, I recommend taking a look at my [AnsiLove.framework](https://github.com/ByteProject/AnsiLove.framework), which is smooth, stable and actively maintained. It uses a modfied version of [AnsiLove/PHP](http://ansilove.sourceforge.net) as rendering library and provides a Cocoa layer on top of it.  Once AnsiLove/C is finished, it will replace [AnsiLove/PHP](http://ansilove.sourceforge.net) in my [AnsiLove.framework](https://github.com/ByteProject/AnsiLove.framework), to go all the way native.

# License

AnsiLove/C is released under a MIT-style license. See the file `LICENSE` for details.
