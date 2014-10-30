#include <ByteStream.h>

// Create an instance of ByteStream. The parameter (50) is the maximum length of the stream in bytes
ByteStream streamWrite(50);

unsigned char buf[40];
unsigned int length;
int i = 14712;
float floatArray[3] = {6.547f, -6.24f, 44784.1123f};

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  // We can write almost any kind of data type to the stream
  streamWrite << 'C' << 'b';
  streamWrite << 'e';
  streamWrite << 'm';
  streamWrite << "bcde" << streamWrite(floatArray, 3) << true << i << 978.415; // We can write arrays to the stream, "streamWrite(array, size)"
  
  // Returns the buffer and length in bytes of the stream we have written
  length = streamWrite.getBuf(buf);
  
  Serial.write(buf, length);
  
  // Remember to clear the stream before writing new data to it
  streamWrite.clear();
  
  delay(1000);
}
