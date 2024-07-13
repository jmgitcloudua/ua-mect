#include "Wave.h"
using namespace std;

int main()
{
	Wave sound(48000, 5);

	sound.Generate(880, SINE_WAVE);

	sound.Save("demodulated.wav");
	sound.Play();

	sound.Modulate(880, 10, 1.0, AMPLITUDE_MODULATION);

	sound.Save("modulated.wav");
	sound.Play();

	sound.Plot(1, 1);

	return 0;
}