#include <ByteStream.h>

// Create an instance of ByteStream. The parameter (50) is the maximum length of our stream in bytes
ByteStream streamRead(50);

unsigned char buf[40];
char c1, c2, c3, c4;
int i;
bool b;
double d;
char string[10];
float floatArray[3];

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  Serial.readBytes((char *)buf, 34);
  
  // Copy the received data to our stream. The second parameter (34) is the length of the received buffer
  streamRead.setBuf(buf, 34);
  
  // We can get the original variables we had written to our stream
  streamRead >> c1 >> c2 >> c3 >> c4 >> string >> streamRead(floatArray, 3);
  streamRead >> b >> i >> d;
  
  delay(1000);
}
