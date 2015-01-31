/*==============================================================================

    Copyright (C) 2014, 2015 Pablo Albiol http://github.com/PabloAlbiol

    ByteStream is free software: you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation, either
    version 3 of the License, or (at your option) any later version.

    ByteStream is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with ByteStream.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/

/*
    ByteStream is a C++ library for encoding and decoding different data types into bytes
    http://github.com/PabloAlbiol/ByteStream
*/

#ifndef BYTESTREAM_H
#define BYTESTREAM_H


class ByteStream
{
    // Array struct forward declaration
    struct Array;

public:
    ByteStream(const unsigned int cap);
    ByteStream(const ByteStream &c); // Copy constructor
    ByteStream &operator=(const ByteStream &c); // Copy assignment operator
    ~ByteStream();

    void clear();
    unsigned int getBuf(unsigned char buf[]);
    unsigned int getCapacity();
    unsigned int getLength();
    void setBuf(const unsigned char buf[], const unsigned int size);

    // Operator << overloading
    ByteStream &operator<<(const bool val);
    ByteStream &operator<<(const unsigned char val);
    ByteStream &operator<<(const char val);
    ByteStream &operator<<(const unsigned short int val);
    ByteStream &operator<<(const short int val);
    ByteStream &operator<<(const unsigned int val);
    ByteStream &operator<<(const int val);
    ByteStream &operator<<(const unsigned long int val);
    ByteStream &operator<<(const long int val);
    ByteStream &operator<<(const unsigned long long int val);
    ByteStream &operator<<(const long long int val);
    ByteStream &operator<<(const float val);
    ByteStream &operator<<(const double val);
    ByteStream &operator<<(const long double val);
    ByteStream &operator<<(const char string[]);
    ByteStream &operator<<(const ByteStream::Array array);

    // Operator >> overloading
    ByteStream &operator>>(const bool &val);
    ByteStream &operator>>(const unsigned char &val);
    ByteStream &operator>>(const char &val);
    ByteStream &operator>>(const unsigned short int &val);
    ByteStream &operator>>(const short int &val);
    ByteStream &operator>>(const unsigned int &val);
    ByteStream &operator>>(const int &val);
    ByteStream &operator>>(const unsigned long int &val);
    ByteStream &operator>>(const long int &val);
    ByteStream &operator>>(const unsigned long long int &val);
    ByteStream &operator>>(const long long int &val);
    ByteStream &operator>>(const float &val);
    ByteStream &operator>>(const double &val);
    ByteStream &operator>>(const long double &val);
    ByteStream &operator>>(const char string[]);
    ByteStream &operator>>(const ByteStream::Array &array);

    // Operator () overloading
    ByteStream::Array operator()(bool buf[], const unsigned int size);
    ByteStream::Array operator()(unsigned char buf[], const unsigned int size);
    ByteStream::Array operator()(char buf[], const unsigned int size);
    ByteStream::Array operator()(unsigned short int buf[], const unsigned int size);
    ByteStream::Array operator()(short int buf[], const unsigned int size);
    ByteStream::Array operator()(unsigned int buf[], const unsigned int size);
    ByteStream::Array operator()(int buf[], const unsigned int size);
    ByteStream::Array operator()(unsigned long int buf[], const unsigned int size);
    ByteStream::Array operator()(long int buf[], const unsigned int size);
    ByteStream::Array operator()(unsigned long long int buf[], const unsigned int size);
    ByteStream::Array operator()(long long int buf[], const unsigned int size);
    ByteStream::Array operator()(float buf[], const unsigned int size);
    ByteStream::Array operator()(double buf[], const unsigned int size);
    ByteStream::Array operator()(long double buf[], const unsigned int size);


private:
    void append(const unsigned char byte);
    unsigned char remove();
    void reorder();

    unsigned char *buffer;
    unsigned int capacity;
    unsigned int index;
    unsigned int length;

    // Structure to store arrays and their sizes
    struct Array
    {
        void *bufferArray; // I don't want to store any array, just a pointer
        unsigned int lengthArray;
        unsigned int type;
    };

    enum BS_TYPES
    {
        BS_BOOL,
        BS_UCHAR,
        BS_CHAR,
        BS_USINT,
        BS_SINT,
        BS_UINT,
        BS_INT,
        BS_ULINT,
        BS_LINT,
        BS_ULLINT,
        BS_LLINT,
        BS_FLOAT,
        BS_DOUBLE,
        BS_LDOUBLE
    };
};

#endif // BYTESTREAM_H
