# encoding=utf-8
__author__ = 'labi'
import wave
import sys
import pyaudio

rate = 44100
wv = wave.open("piano.wav", "w")
wv.setparams((1, 2, rate, 0, 'NONE', 'not compressed'))

tones = {\
    1:[697, 1029],2:[697, 1336],\
    3:[697, 1477],4:[770, 1209],\
    5:[770, 1336], 6:[770, 1477],\
    7:[852, 1209], 8:[852, 1336],\
    9:[852, 1477], 0:[941, 1336]}
number = [2, 3, 4, 7, 4, 8] # numero a codificar
data = []

for n in number:
    # Codigos DTMF

    for i in range(0, int(rate*0.040)):
        data.append(tones[1])

    # Pausa (silêncio)

    for i in range(0, int(rate*0.040)):
        data.append([0,0])
wv.close()