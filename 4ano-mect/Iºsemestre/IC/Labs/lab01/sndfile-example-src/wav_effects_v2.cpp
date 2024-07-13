#include <iostream>
//#include <conio.h>
#include <fstream>
#ifndef endl
#define endl "\n"
#endif

#define wav_eco(filin, fileout, eco_rate)                   \
    char temp[2];                                           \
    char ch[eco_rate][2], ch2[eco_rate][2];                 \
    int i, j;                                               \
    for (i = 0; i < eco_rate; i++)                          \
        for (j = 0; j < 2; j++)                             \
            ch2[i][j] = 0;                                  \
    while (!filin.eof())                                    \
    {                                                       \
        for (i = 0; i < eco_rate && !filin.eof(); i++)      \
            filin.read((char *)&ch[i], sizeof(char[2]));    \
        for (i = 0; i < eco_rate; i++)                      \
        {                                                   \
            temp[0] = ch[i][0];                             \
            temp[1] = ch[i][1];                             \
            ch[i][0] += ch2[i][0];                          \
            ch[i][1] += ch2[i][1];                          \
            fileout.write((char *)&ch[i], sizeof(char[2])); \
            ch2[i][0] = temp[0];                            \
            ch2[i][1] = temp[1];                            \
        }                                                   \
    }

using namespace std;
struct WAVEFILEHEADER
{
    char ChunkId[4];
    int ChunkSize;
    char Format[4];
    char SubChunkFmt[4];
    int SubChunkFmtSize;
    short int AudioFormat;
    short int NumChannels;

    int SampleRate;
    int ByteRate;
    short int BlockAlign;
    short int BitsPerSample;

    char ChunkData[4];
    int SubChunkDataSize;
};

int main()
{
    fstream filin("sample.wav", ios::in | ios::binary);
    fstream fileout("wav_effects_v2_out.wav", ios::out | ios::binary);
    WAVEFILEHEADER wav;
    filin.read((char *)&wav, sizeof(wav));
    // to display the contents of the header
    /*cout << wav.ByteRate
         << endl
         << wav.ChunkSize
         << endl
         << wav.SampleRate // no of samples per second
         << endl
         << wav.SubChunkDataSize
         << endl
         << wav.SubChunkFmtSize
         << endl
         << wav.ChunkData
         << endl
         << wav.ChunkId
         << endl
         << wav.Format
         << endl
         << wav.SubChunkFmt
         << endl
         << wav.AudioFormat
         << endl
         << wav.AudioFormat
         << endl
         << wav.BitsPerSample // no of bits per second
         << endl
         << wav.BlockAlign
         << endl
         << wav.NumChannels
         << endl
         << endl
         << sizeof(wav);*/
    /* size of the wav variable*/
    // getch();
    fileout.write((char *)&wav, sizeof(wav)); /// write the header to output file
    wav_eco(filin, fileout, 2000000);         /// modify the data and update the output file
    filin.close();
    fileout.close();
    return 0;
}

/*algorithm implemented by the wav_eco function(this is not some stranded algorithm. I wrote it myself)  :-
1) obtain the 'echo_rate' of the samples
2) read the data present in the original wav file
3) write this data, by adding each sample from the previously obtained data to the data that was read now
4) follow steps 2 and 3 until eof is reached
  */