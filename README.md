# AnsiLove/ObjC

This is an attempt of porting [AnsiLove/PHP](http://ansilove.sourceforge.net) to `Objective-C`. Right now it's in an early stage of development and I won't guarantee it will ever be finished. If you're looking for something to implement into your Cocoa or Foundation applications, I recommend taking a look at my [AnsiLove.framework](https://github.com/ByteProject/AnsiLove.framework), which is smooth, stable and actively maintained. There is no specific timeframe for AnsiLove/ObjC.

# Goals

The project is a Foundation tool, primary aimed to compile on Mac OS X. Anyway, I'm going to use `ANSI C` wherever I can (preferably everywhere) because I want AnsiLove/ObjC to be easy portable to other operating systems. Once it is finished, it will replace the [AnsiLove/PHP](http://ansilove.sourceforge.net) rendering library in my [AnsiLove.framework](https://github.com/ByteProject/AnsiLove.framework). You may ask why a rewrite to C/ObjC if the Cocoa framework is already up and running with a PHP library underneath? 

- Challenge
- PHP interpreter independence
- Performance

# License

AnsiLove/ObjC is released under a MIT-style license. See the file `LICENSE` for details.
