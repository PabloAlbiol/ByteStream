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
    unsigned char byte = 0; // Not the best solution
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

ByteStream &ByteStream::operator<<(const ByteStream::Array<bool> array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this << array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const ByteStream::Array<unsigned char> array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this << array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const ByteStream::Array<char> array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this << array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const ByteStream::Array<unsigned short int> array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this << array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const ByteStream::Array<short int> array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this << array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const ByteStream::Array<unsigned int> array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this << array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const ByteStream::Array<int> array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this << array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const ByteStream::Array<unsigned long int> array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this << array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const ByteStream::Array<long int> array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this << array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const ByteStream::Array<unsigned long long int> array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this << array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const ByteStream::Array<long long int> array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this << array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const ByteStream::Array<float> array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this << array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const ByteStream::Array<double> array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this << array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator<<(const ByteStream::Array<long double> array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this << array.bufferArray[i];
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

ByteStream &ByteStream::operator>>(const ByteStream::Array<bool> &array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this >> array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const ByteStream::Array<unsigned char> &array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this >> array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const ByteStream::Array<char> &array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this >> array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const ByteStream::Array<unsigned short int> &array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this >> array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const ByteStream::Array<short int> &array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this >> array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const ByteStream::Array<unsigned int> &array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this >> array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const ByteStream::Array<int> &array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this >> array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const ByteStream::Array<unsigned long int> &array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this >> array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const ByteStream::Array<long int> &array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this >> array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const ByteStream::Array<unsigned long long int> &array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this >> array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const ByteStream::Array<long long int> &array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this >> array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const ByteStream::Array<float> &array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this >> array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const ByteStream::Array<double> &array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this >> array.bufferArray[i];
    }
    return *this;
}

ByteStream &ByteStream::operator>>(const ByteStream::Array<long double> &array)
{
    for (unsigned int i = 0; i < array.lengthArray; i++)
    {
        *this >> array.bufferArray[i];
    }
    return *this;
}


// Operator () overloading

ByteStream::Array<bool> ByteStream::operator()(bool buf[], const unsigned int size)
{
    Array<bool> array(buf, size);
    return array;
}

ByteStream::Array<unsigned char> ByteStream::operator()(unsigned char buf[], const unsigned int size)
{
    Array<unsigned char> array(buf, size);
    return array;
}

ByteStream::Array<char> ByteStream::operator()(char buf[], const unsigned int size)
{
    Array<char> array(buf, size);
    return array;
}

ByteStream::Array<unsigned short int> ByteStream::operator()(unsigned short int buf[], const unsigned int size)
{
    Array<unsigned short int> array(buf, size);
    return array;
}

ByteStream::Array<short int> ByteStream::operator()(short int buf[], const unsigned int size)
{
    Array<short int> array(buf, size);
    return array;
}

ByteStream::Array<unsigned int> ByteStream::operator()(unsigned int buf[], const unsigned int size)
{
    Array<unsigned int> array(buf, size);
    return array;
}

ByteStream::Array<int> ByteStream::operator()(int buf[], const unsigned int size)
{
    Array<int> array(buf, size);
    return array;
}

ByteStream::Array<unsigned long int> ByteStream::operator()(unsigned long int buf[], const unsigned int size)
{
    Array<unsigned long int> array(buf, size);
    return array;
}

ByteStream::Array<long int> ByteStream::operator()(long int buf[], const unsigned int size)
{
    Array<long int> array(buf, size);
    return array;
}

ByteStream::Array<unsigned long long int> ByteStream::operator()(unsigned long long int buf[], const unsigned int size)
{
    Array<unsigned long long int> array(buf, size);
    return array;
}

ByteStream::Array<long long int> ByteStream::operator()(long long int buf[], const unsigned int size)
{
    Array<long long int> array(buf, size);
    return array;
}

ByteStream::Array<float> ByteStream::operator()(float buf[], const unsigned int size)
{
    Array<float> array(buf, size);
    return array;
}

ByteStream::Array<double> ByteStream::operator()(double buf[], const unsigned int size)
{
    Array<double> array(buf, size);
    return array;
}

ByteStream::Array<long double> ByteStream::operator()(long double buf[], const unsigned int size)
{
    Array<long double> array(buf, size);
    return array;
}
