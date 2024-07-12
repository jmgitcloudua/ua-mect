from struct import pack
from math import sin, pi
import wave
import sys

def main(argv):
    rate = 44100
    wv = wave.open("piano.wav", "w")
    wv.setparams((1, 2, rate, 0, 'NONE', 'not compressed'))
    
    amplitude = 10000
    data = []
    freq_a = 440
    freq_b = 880
    duration = 5
    for i in range(0, rate*duration):
        data.append(amplitude*sin(2*pi*freq_a*i/rate) + amplitude*sin(2*pi*freq_b*i/rate))
        
    wvData = ''
    for v in data:
        wvData += pack('h', v)
        
    wv.writeframes(wvData)
    wv.close()
main(sys.argv)