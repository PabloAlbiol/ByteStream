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

#include "ByteStream.h"
#include <iostream>
#include <cstring>


ByteStream::ByteStream(const unsigned int cap)
{
    // Buffer array. Stores the byte stream
    buffer = NULL;

    // Buffer capacity. Memory available
    capacity = cap;
    // Buffer index. Position where the next byte will be read
    index = 0;
    // Buffer length
    length = 0;

    try
    {
        // Create buffer array dynamically
        buffer = new unsigned char[cap];
    }
    catch(std::bad_alloc)
    {
        // Not enough memory
        capacity = 0;
    }
}

ByteStream::ByteStream(const ByteStream &c)
{
    buffer = NULL;
    capacity = c.capacity;
    index = c.index;
    length = c.length;

    try
    {
        buffer = new unsigned char[capacity];
        memcpy(buffer, c.buffer, capacity*sizeof(unsigned char));
    }
    catch(std::bad_alloc)
    {
        // Not enough memory
        capacity = 0;
        index = 0;
        length = 0;
    }
}

ByteStream &ByteStream::operator=(const ByteStream &c)
{
    if (this != &c)
    {
        capacity = c.capacity;
        index = c.index;
        length = c.length;

        delete[] buffer;
        if (c.buffer)
        {
            try
            {
                buffer = new unsigned char[capacity];
                memcpy(buffer, c.buffer, capacity*sizeof(unsigned char));
            }
            catch(std::bad_alloc)
            {
                // Not enough memory
                capacity = 0;
                index = 0;
                length = 0;
            }
        }
        else buffer = NULL;
    }
    return *this;
}

ByteStream::~ByteStream()
{
    // Free memory
    if (buffer != NULL)
    {
        delete[] buffer;
    }
}


void ByteStream::append(const unsigned char byte)
{
    if (length < (capacity - index ))
    {
        buffer[length + index] = byte;
        length++;
    }
    else if (index > 0)
    {
        reorder();
        append(byte);
    }
}

void ByteStream::clear()
{
    index = 0;
    length = 0;
}

unsigned int ByteStream::getBuf(unsigned char buf[])
{
    if (index > 0)
    {
        reorder();
    }

    // Copy the buffer array
    memcpy(buf, buffer, length*sizeof(unsigned char));

    return length;
}

unsigned int ByteStream::getCapacity()
{
    return capacity;
}

unsigned int ByteStream::getLength()
{
    return length;
}

unsigned char ByteStream::remove()
{
    unsigned char byte = 0; // Not the best solution, it returns a 0 if length = 0
    if (length > 0)
    {
        byte = buffer[index];
        index++;
        length--;
    }
    return byte;
}

void ByteStream::reorder()
{
    for (unsigned int i = 0; i < capacity; i++)
    {
        buffer[i] = buffer[i + index];
    }
    index = 0;
}

void ByteStream::setBuf(const unsigned char buf[], const unsigned int size)
{
    if (size <= capacity)
    {
        // Copy the buffer array
        memcpy(buffer, buf, size*sizeof(unsigned char));

        length = size;
        index = 0;
    }
    else
    {
        // Not enough memory
        index = 0;
        length = 0;
    }
}


// Operator << overloading

ByteStream &ByteStream::operator<<(const bool val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(bool); i++)
    {
        append(pointer[i]);
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const unsigned char val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(unsigned char); i++)
    {
        append(pointer[i]);
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const char val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(char); i++)
    {
        append(pointer[i]);
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const unsigned short int val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(unsigned short int); i++)
    {
        append(pointer[i]);
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const short int val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(short int); i++)
    {
        append(pointer[i]);
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const unsigned int val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(unsigned int); i++)
    {
        append(pointer[i]);
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const int val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(int); i++)
    {
        append(pointer[i]);
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const unsigned long int val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(unsigned long int); i++)
    {
        append(pointer[i]);
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const long int val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(long int); i++)
    {
        append(pointer[i]);
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const unsigned long long int val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(unsigned long long int); i++)
    {
        append(pointer[i]);
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const long long int val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(long long int); i++)
    {
        append(pointer[i]);
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const float val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(float); i++)
    {
        append(pointer[i]);
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const double val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(double); i++)
    {
        append(pointer[i]);
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const long double val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(long double); i++)
    {
        append(pointer[i]);
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const char string[])
{
    for (unsigned int i = 0; i < (strlen(string) + 1); i++)
    {
        *this << string[i];
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const ByteStream::Array array)
{
    switch (array.type)
    {
        case BS_BOOL:
        {
            bool *pointer = (bool *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this << pointer[i];
            }
        }
        break;

        case BS_UCHAR:
        {
            unsigned char *pointer = (unsigned char *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this << pointer[i];
            }
        }
        break;

        case BS_CHAR:
        {
            char *pointer = (char *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this << pointer[i];
            }
        }
        break;

        case BS_USINT:
        {
            unsigned short int *pointer = (unsigned short int *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this << pointer[i];
            }
        }
        break;

        case BS_SINT:
        {
            short int *pointer = (short int *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this << pointer[i];
            }
        }
        break;

        case BS_UINT:
        {
            unsigned int *pointer = (unsigned int *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this << pointer[i];
            }
        }
        break;

        case BS_INT:
        {
            int *pointer = (int *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this << pointer[i];
            }
        }
        break;

        case BS_ULINT:
        {
            unsigned long int *pointer = (unsigned long int *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this << pointer[i];
            }
        }
        break;

        case BS_LINT:
        {
            long int *pointer = (long int *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this << pointer[i];
            }
        }
        break;

        case BS_ULLINT:
        {
            unsigned long long int *pointer = (unsigned long long int *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this << pointer[i];
            }
        }
        break;

        case BS_LLINT:
        {
            long long int *pointer = (long long int *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this << pointer[i];
            }
        }
        break;

        case BS_FLOAT:
        {
            float *pointer = (float *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this << pointer[i];
            }
        }
        break;

        case BS_DOUBLE:
        {
            double *pointer = (double *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this << pointer[i];
            }
        }
        break;

        case BS_LDOUBLE:
        {
            long double *pointer = (long double *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this << pointer[i];
            }
        }
        break;
    }
    return *this;
}


// Operator >> overloading

ByteStream &ByteStream::operator>>(const bool &val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(bool); i++)
    {
        pointer[i] = remove();
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const unsigned char &val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(unsigned char); i++)
    {
        pointer[i] = remove();
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const char &val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(char); i++)
    {
        pointer[i] = remove();
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const unsigned short int &val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(unsigned short int); i++)
    {
        pointer[i] = remove();
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const short int &val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(short int); i++)
    {
        pointer[i] = remove();
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const unsigned int &val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(unsigned int); i++)
    {
        pointer[i] = remove();
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const int &val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(int); i++)
    {
        pointer[i] = remove();
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const unsigned long int &val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(unsigned long int); i++)
    {
        pointer[i] = remove();
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const long int &val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(long int); i++)
    {
        pointer[i] = remove();
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const unsigned long long int &val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(unsigned long long int); i++)
    {
        pointer[i] = remove();
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const long long int &val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(long long int); i++)
    {
        pointer[i] = remove();
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const float &val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(float); i++)
    {
        pointer[i] = remove();
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const double &val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(double); i++)
    {
        pointer[i] = remove();
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const long double &val)
{
    unsigned char *pointer = (unsigned char *)&val;
    for (unsigned int i = 0; i < sizeof(long double); i++)
    {
        pointer[i] = remove();
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const char string[])
{
    unsigned int i = 0;

    while(buffer[index - 1] != 0 && length > 0)
    {
        *this >> string[i];
        i++;
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const ByteStream::Array &array)
{
    switch (array.type)
    {
        case BS_BOOL:
        {
            bool *pointer = (bool *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this >> pointer[i];
            }
        }
        break;

        case BS_UCHAR:
        {
            unsigned char *pointer = (unsigned char *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this >> pointer[i];
            }
        }
        break;

        case BS_CHAR:
        {
            char *pointer = (char *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this >> pointer[i];
            }
        }
        break;

        case BS_USINT:
        {
            unsigned short int *pointer = (unsigned short int *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this >> pointer[i];
            }
        }
        break;

        case BS_SINT:
        {
            short int *pointer = (short int *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this >> pointer[i];
            }
        }
        break;

        case BS_UINT:
        {
            unsigned int *pointer = (unsigned int *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this >> pointer[i];
            }
        }
        break;

        case BS_INT:
        {
            int *pointer = (int *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this >> pointer[i];
            }
        }
        break;

        case BS_ULINT:
        {
            unsigned long int *pointer = (unsigned long int *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this >> pointer[i];
            }
        }
        break;

        case BS_LINT:
        {
            long int *pointer = (long int *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this >> pointer[i];
            }
        }
        break;

        case BS_ULLINT:
        {
            unsigned long long int *pointer = (unsigned long long int *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this >> pointer[i];
            }
        }
        break;

        case BS_LLINT:
        {
            long long int *pointer = (long long int *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this >> pointer[i];
            }
        }
        break;

        case BS_FLOAT:
        {
            float *pointer = (float *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this >> pointer[i];
            }
        }
        break;

        case BS_DOUBLE:
        {
            double *pointer = (double *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this >> pointer[i];
            }
        }
        break;

        case BS_LDOUBLE:
        {
            long double *pointer = (long double *)array.bufferArray;
            for (unsigned int i = 0; i < array.lengthArray; i++)
            {
                *this >> pointer[i];
            }
        }
        break;
    }
    return *this;
}


// Operator () overloading

ByteStream::Array ByteStream::operator()(bool buf[], const unsigned int size)
{
    Array structArray;
    structArray.lengthArray = size;
    structArray.bufferArray = buf;
    structArray.type = BS_BOOL;
    return structArray;
}

ByteStream::Array ByteStream::operator()(unsigned char buf[], const unsigned int size)
{
    Array structArray;
    structArray.lengthArray = size;
    structArray.bufferArray = buf;
    structArray.type = BS_UCHAR;
    return structArray;
}

ByteStream::Array ByteStream::operator()(char buf[], const unsigned int size)
{
    Array structArray;
    structArray.lengthArray = size;
    structArray.bufferArray = buf;
    structArray.type = BS_CHAR;
    return structArray;
}

ByteStream::Array ByteStream::operator()(unsigned short int buf[], const unsigned int size)
{
    Array structArray;
    structArray.lengthArray = size;
    structArray.bufferArray = buf;
    structArray.type = BS_USINT;
    return structArray;
}

ByteStream::Array ByteStream::operator()(short int buf[], const unsigned int size)
{
    Array structArray;
    structArray.lengthArray = size;
    structArray.bufferArray = buf;
    structArray.type = BS_SINT;
    return structArray;
}

ByteStream::Array ByteStream::operator()(unsigned int buf[], const unsigned int size)
{
    Array structArray;
    structArray.lengthArray = size;
    structArray.bufferArray = buf;
    structArray.type = BS_UINT;
    return structArray;
}

ByteStream::Array ByteStream::operator()(int buf[], const unsigned int size)
{
    Array structArray;
    structArray.lengthArray = size;
    structArray.bufferArray = buf;
    structArray.type = BS_INT;
    return structArray;
}

ByteStream::Array ByteStream::operator()(unsigned long int buf[], const unsigned int size)
{
    Array structArray;
    structArray.lengthArray = size;
    structArray.bufferArray = buf;
    structArray.type = BS_ULINT;
    return structArray;
}

ByteStream::Array ByteStream::operator()(long int buf[], const unsigned int size)
{
    Array structArray;
    structArray.lengthArray = size;
    structArray.bufferArray = buf;
    structArray.type = BS_LINT;
    return structArray;
}

ByteStream::Array ByteStream::operator()(unsigned long long int buf[], const unsigned int size)
{
    Array structArray;
    structArray.lengthArray = size;
    structArray.bufferArray = buf;
    structArray.type = BS_ULLINT;
    return structArray;
}

ByteStream::Array ByteStream::operator()(long long int buf[], const unsigned int size)
{
    Array structArray;
    structArray.lengthArray = size;
    structArray.bufferArray = buf;
    structArray.type = BS_LLINT;
    return structArray;
}

ByteStream::Array ByteStream::operator()(float buf[], const unsigned int size)
{
    Array structArray;
    structArray.lengthArray = size;
    structArray.bufferArray = buf;
    structArray.type = BS_FLOAT;
    return structArray;
}

ByteStream::Array ByteStream::operator()(double buf[], const unsigned int size)
{
    Array structArray;
    structArray.lengthArray = size;
    structArray.bufferArray = buf;
    structArray.type = BS_DOUBLE;
    return structArray;
}

ByteStream::Array ByteStream::operator()(long double buf[], const unsigned int size)
{
    Array structArray;
    structArray.lengthArray = size;
    structArray.bufferArray = buf;
    structArray.type = BS_LDOUBLE;
    return structArray;
}
