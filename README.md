## ByteStream ##

ByteStream is a C++ library that handles the conversion of different data types into arrays of bytes and vice versa.

This library supports differents data types: chars, ints, floats, doubles, arrays of ints, arrays of floats, arrays os doubles, strings, etc.

ByteStream is meant to be used for making communication tasks easier. As it has been programmed in C++, it can be used in many embedded systems. For example: Serial communication on Arduino.

### Usage ###

Using ByteStream is easy. It works like a stream where data can be put on and taken out.

To put on data into the stream:

    myStream << 124 << 'z' << 147.47 << "abcde";

To take out data of the stream:

    myStream >> vInt >> vChar >> vDouble >> vString;

Where vInt, vChar, vDouble, vString are variables where the data will be stored.

This library also comes with more examples. For further information, see examples inside.

### License ###

ByteStream is licensed under the terms of the GNU Lesser General Public License (version 3). You can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Copyright (C) 2014, 2015 Pablo Albiol http://github.com/PabloAlbiol

