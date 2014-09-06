#ifndef BYTESTREAM_H
#define BYTESTREAM_H


class ByteStream
{
    // Array class forward declaration
    template <class T>
    class Array;

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

    ByteStream &operator<<(const ByteStream::Array<bool> array);
    ByteStream &operator<<(const ByteStream::Array<unsigned char> array);
    ByteStream &operator<<(const ByteStream::Array<char> array);
    ByteStream &operator<<(const ByteStream::Array<unsigned short int> array);
    ByteStream &operator<<(const ByteStream::Array<short int> array);
    ByteStream &operator<<(const ByteStream::Array<unsigned int> array);
    ByteStream &operator<<(const ByteStream::Array<int> array);
    ByteStream &operator<<(const ByteStream::Array<unsigned long int> array);
    ByteStream &operator<<(const ByteStream::Array<long int> array);
    ByteStream &operator<<(const ByteStream::Array<unsigned long long int> array);
    ByteStream &operator<<(const ByteStream::Array<long long int> array);
    ByteStream &operator<<(const ByteStream::Array<float> array);
    ByteStream &operator<<(const ByteStream::Array<double> array);
    ByteStream &operator<<(const ByteStream::Array<long double> array);

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

    ByteStream &operator>>(const ByteStream::Array<bool> &array);
    ByteStream &operator>>(const ByteStream::Array<unsigned char> &array);
    ByteStream &operator>>(const ByteStream::Array<char> &array);
    ByteStream &operator>>(const ByteStream::Array<unsigned short int> &array);
    ByteStream &operator>>(const ByteStream::Array<short int> &array);
    ByteStream &operator>>(const ByteStream::Array<unsigned int> &array);
    ByteStream &operator>>(const ByteStream::Array<int> &array);
    ByteStream &operator>>(const ByteStream::Array<unsigned long int> &array);
    ByteStream &operator>>(const ByteStream::Array<long int> &array);
    ByteStream &operator>>(const ByteStream::Array<unsigned long long int> &array);
    ByteStream &operator>>(const ByteStream::Array<long long int> &array);
    ByteStream &operator>>(const ByteStream::Array<float> &array);
    ByteStream &operator>>(const ByteStream::Array<double> &array);
    ByteStream &operator>>(const ByteStream::Array<long double> &array);

    // Operator () overloading
    ByteStream::Array<bool> operator()(bool buf[], const unsigned int size);
    ByteStream::Array<unsigned char> operator()(unsigned char buf[], const unsigned int size);
    ByteStream::Array<char> operator()(char buf[], const unsigned int size);
    ByteStream::Array<unsigned short int> operator()(unsigned short int buf[], const unsigned int size);
    ByteStream::Array<short int> operator()(short int buf[], const unsigned int size);
    ByteStream::Array<unsigned int> operator()(unsigned int buf[], const unsigned int size);
    ByteStream::Array<int> operator()(int buf[], const unsigned int size);
    ByteStream::Array<unsigned long int> operator()(unsigned long int buf[], const unsigned int size);
    ByteStream::Array<long int> operator()(long int buf[], const unsigned int size);
    ByteStream::Array<unsigned long long int> operator()(unsigned long long int buf[], const unsigned int size);
    ByteStream::Array<long long int> operator()(long long int buf[], const unsigned int size);
    ByteStream::Array<float> operator()(float buf[], const unsigned int size);
    ByteStream::Array<double> operator()(double buf[], const unsigned int size);
    ByteStream::Array<long double> operator()(long double buf[], const unsigned int size);

private:
    void append(const unsigned char byte);
    unsigned char remove();
    void reorder();

    unsigned char *buffer;
    unsigned int capacity;
    unsigned int index;
    unsigned int length;

    // Class to store arrays and their sizes
    template <class T>
    class Array
    {
    public:
        Array(T buf[], const unsigned int size)
        {
            lengthArray = size;

            // I don't want to store any array, just a pointer
            bufferArray = buf;
        }
        Array(const Array &c) // Copy constructor. Not necessary
        {
            lengthArray = c.lengthArray;
            bufferArray = c.bufferArray;
        }
        Array &operator=(const Array &c) // Copy assignment operator. Not necessary
        {
            if (this != &c)
            {
                lengthArray = c.lengthArray;
                bufferArray = c.bufferArray;
            }
            return *this;
        }
        ~Array() // Destructor. Not necessary
        {
        }
        T *bufferArray;
        unsigned int lengthArray;
    };
};

#endif // BYTESTREAM_H
