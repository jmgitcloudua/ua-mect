import signal
import socket
import sys
import psutil
import time
from colorama import Fore

intro = Fore.GREEN + '''
        
        #############################################################
        #       FINAL PROJECT RC-I | 1st Simester | 2021-2022       #           
        #       Jodionísio Muachifi - 97147                         #
        #       Diogo Santos - 98393                                #
        #############################################################
'''
print(intro + "\n")

def signal_handler(sg, fr):
    print("\nDone Successfully!")
    sys.exit(0)

print(Fore.CYAN +" ######## CLIENT START #########")
signal.signal(signal.SIGINT, signal_handler)
print("Press Ctrl+C to exit ...")



ip = "127.0.0.1"
port = 8008

socketTCP = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socketTCP.connect((ip, port))

while True:
    try:
        msg = ("CPU: "+str(psutil.cpu_percent())+" %   Memory: "+str(psutil.virtual_memory()[2])+"%").encode()
        if len(msg)>0:
            socketTCP.send(msg)
            response = socketTCP.recv(4096).decode()
            print("Server response: {}".format(response))
        time.sleep(2)
    except (socket.timeout, socket.error):
        print("Server error. Out!")
        sys.exit(0)
