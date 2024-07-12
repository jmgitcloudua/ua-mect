import wave
import sys
import pyaudio

def main(argv):
    wf = wave.open("Crazed-Bells.wav", "rb")
    print wf.getnchannels()
    print wf.getframerate()
    print wf.getsampwidth()
    print wf.getnframes()
    
    player = pyaudio.PyAudio()
    
    stream = player.open(format = player.get_format_from_width(wf.getsampwidth()), channels =wf.getnchannels(),rate =wf.getframerate(),output = True)
    
    while True:
        data = wf.readframes(1024)
        if not data:
            break
        
        stream.write(data)
    stream.close()
    player.terminate()
    wf.close()

main(sys.argv)
