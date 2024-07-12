# encoding=utf-8

__author__ = 'labi'

import wave
import struct
import sys
from struct import pack
import math
import random

def copy(data):
    output = []
    for index,value in enumerate(data):
        output.append(value)
    return output

def reverse(data):
    output = []
    for index,value in enumerate(reversed(data)):
        output.append(value)
    return output

def volume(data, factor):
    output = []
    factor = float(factor)

    for index, value in enumerate(data):
        output.append(value*factor)

    return output

def fadein(data, sample_rate, duration):
    output = []
    duration = float(duration)
    time_start = 0
    time_stop = duration * sample_rate
    step = 1.0 / (sample_rate * duration)

    for index, value in enumerate(data):
        time = index
        if time>time_start and time<time_stop:
            output.append(value*index*step)
        else:
            output.append(value)

    return output

def fadeout(data, sample_rate, duration):

    output = []
    sample_rate = float(sample_rate)
    duration = float(duration)
    index = 0
    for index, value in enumerate(data):
        pass

    time_start = index-(duration * sample_rate)
    time_stop = index
    step = 1.0 / (sample_rate * duration)

    for index2, value in enumerate(data):
        time = index2
        if time>time_start and time<time_stop:
            output.append(value*(index-index2)*step)
        else:
            output.append(value)

    return output

def normalize(data):
    output = []
    val_max = 32767
    max = 0

    for index, value in enumerate(data):
        if(abs(value)>max):
            max = abs(value)

    output = volume(data, val_max/max)

    return output

def mask(data, sample_rate, masktype, start, duration):

    output = []
    start = float(start) * sample_rate
    duration = float(duration) * sample_rate
    end = start + duration

    for index, value in enumerate(data):
        if index>start and index<end:
            if(masktype=='silence'):
                output.append(0)
            elif(masktype=='noise'):
                output.append(random.randint(-32768, 32767))
            elif(masktype=='tone'):
                output.append(10000*math.sin(2*math.pi*440*index/sample_rate))
            else:
                output.append(value)
        else:
            output.append(value)
    return output

def modulate(data, sample_rate, freq):
    output = []

    freq = int(freq)

    for index, value in enumerate(data):
        output.append(value*math.sin(2*math.pi*freq*index/sample_rate))

    return output

def delay(data, sample_rate, amount, t_delay):
    amount = float(amount)
    t_delay = float(t_delay)

    output = [0] *len(data)

    tdelay = t_delay * sample_rate

    for index,value in enumerate(data):
        if index+int(tdelay)<len(output):
            output[index] = value
            output[index+int(tdelay)] += value * amount
        else:
            output[index] = value

    return output

#def tdelay(data, sample_rate, amount, delay):
 #   if amount < 0.05:
 #       return data



#    return tdelay(data, sample_rate, amount*0.8, delay*1.2)

#def steg_add(data, message):
#    bitstream = '01110101' # Irá conter uma string. ex: ’011101010’
#    for c in message:
#        bitstream += format(ord(c),2)

#    output = []
#    encoded_bit = 0
#    for index, value in enumerate(data):
#        output.append()


def main(argv):

    stream = wave.open(argv[1],"rb")
    sample_rate = stream.getframerate()
    num_frames = stream.getnframes()
    raw_data = stream.readframes( num_frames )
    stream.close()
    data = struct.unpack('%dh' % num_frames, raw_data) #’B’ para ficheiros 8bits

    #Aplica efeito sobre data, para output_data

    output_data = []

    i = 0
    while i < len(argv):
        if argv[i] == 'copy':
            output_data = copy(data)
        elif argv[i] == 'reverse':
            output_data = reverse(data)
        elif argv[i] == 'volume':
            output_data = volume(data, argv[i+1])
        elif(argv[i] == 'normalize'):
            output_data = normalize(data)
        elif(argv[i] == 'fade-in'):
            output_data = fadein(data, sample_rate, argv[i+1])
        elif(argv[i] == 'fade-out'):
            output_data = fadeout(data, sample_rate, argv[i+1])
        elif(argv[i] == 'mask'):
            output_data = mask(data, sample_rate, argv[i+1], argv[i+2], argv[i+3])
        elif(argv[i] == 'modulate'):
            output_data = modulate(data, sample_rate, argv[i+1])
#        elif(argv[i] == 'delay'):
#            output_data = delay(data,sample_rate, argv[i+1], argv[i+2])
#        elif(argv[i] == 'steg_add'):
#            output_data = steg_add()
        i=i+1


    wvData=''
    for v in output_data:
        wvData += pack('h',v)

    stream = wave.open('out-'+argv[1], 'wb')
    stream.setnchannels(1)
    stream.setsampwidth(2)
    stream.setframerate(sample_rate)
    stream.setnframes(len(wvData))
    stream.writeframes(wvData)
    stream.close()

if len(sys.argv) < 3:
    print 'Usage: %s wave-file filter1 <params> filter2 <params> ...' % sys.argv[0]
else:
    main(sys.argv)