#include <iostream>
#include <vector>
#include <math.h>
#include "AudioFile.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Command line arguments processing
    if (argc != 2)
    {
        cout << "\033[1;31mError: Usage sintax is ./wav_effects_v1 <input filename>\033[0m" << endl;
        return 0;
    }
    char *inputfile = argv[1];

    // AudioFile
    AudioFile<double> af;
    af.shouldLogErrorsToConsole(false);

    // Load audiofile
    if (af.load(inputfile) == 0)
    {
        cout << "\033[1;31mERROR: File doesn't exist or otherwise can't load file\033[0m" << endl;
        return 0;
    }

    // Get audiofile meta information
    int numChannels = af.getNumChannels();
    int numSamples = af.getNumSamplesPerChannel();
    vector<double> samples;
    double output;
    int gain = 1;
    int k = 0;
    for (int i = 0; i < numChannels; i++)
    {
        for (int j = 0; j < numSamples; j++)
        {
            af.samples[i][j] = af.samples[i][j] + gain * af.samples[i - k][j - k];
            samples.push_back(af.samples[i][j]);
        }
        k++;
    }

    af.save("wav_effects_v1.wav");
}