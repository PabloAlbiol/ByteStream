#include "ByteStream.h"
#include <iostream>

int main(int argc, char *argv[])
{
    ByteStream stream(50);

    unsigned char buf[50];
    unsigned int length;
    char c1, c2, c3, c4;
    int i1 = 14712;
    int i2;
    bool b1;
    double d1;
    char string1[10];
    float floatArray1[3] = {6.547f, -6.24f, 44784.1123f};
    float floatArray2[3];

    std::cout << "Encode" << std::endl;

    stream << 'C' << 'b';
    stream << 'e';
    stream << 'm';
    stream << "bcde" << stream(floatArray1,3) << true << i1 << 978.415;

    length = stream.getBuf(buf);
    std::cout << "Length: " << length << std::endl;
    for (unsigned int i = 0; i < length; i++)
    {
        std::cout << i << " " << buf[i] << std::endl;
    }

    std::cout << "Decode" << std::endl;

    stream >> c1 >> c2 >> c3 >> c4 >> string1 >> stream(floatArray2,3);
    stream >> b1 >> i2 >> d1;

    std::cout << c1 << " " << c2 << " " << c3 << " " << c4 << std::endl;
    std::cout << floatArray2[0] << " " << floatArray2[1] << " " << floatArray2[2] << std::endl;
    std::cout << string1 << std::endl;
    std::cout << b1 << " " << i2 << " " << d1 << std::endl;

    std::cin.get();

    return 0;
}
