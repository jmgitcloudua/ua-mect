// g++ test_BitStream_readBit.cpp -o test_BitStream_readBit

#include "BitStream.cpp"
#include "util.cpp"

void printAsBinary(char byte[]);
void printAsChar(char byte[]);

int main()
{
    BitStream bs("file.bin", 'r');

    char byte[8];

    // read 8 bits (1 byte)
    for (int i = 0; i < 8; i++)
    {
        byte[i] = bs.readBit();
    }
    // print it
    printAsBinary(byte);
    printAsChar(byte);

    // read another 8 bits
    for (int i = 0; i < 8; i++)
    {
        byte[i] = bs.readBit();
    }
    // print
    printAsBinary(byte);
    printAsChar(byte);

    // read plus 6 bits
    printf("%d\n", bs.readBit());
    printf("%d\n", bs.readBit());
    printf("%d\n", bs.readBit());
    printf("%d\n", bs.readBit());
    printf("%d\n", bs.readBit());
    printf("%d\n", bs.readBit());
}
