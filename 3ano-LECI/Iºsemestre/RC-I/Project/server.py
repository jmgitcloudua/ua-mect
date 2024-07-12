import socket
import threading
import signal
import sys
from colorama import Fore

intro = Fore.GREEN +  '''
        #############################################################
        #       FINAL PROJECT RC-I | 1st Simester | 2021-2022       #           
        #       Jodionísio Muachifi - 97147                         #
        #       Diogo Santos - 98393                                #
        #############################################################
'''
print( intro + "\n")

def signal_handler(sg, fr):
    print("\nDone Successfully!")
    sys.exit(0)
print(Fore.RED +"######## SERVER START #########")
signal.signal(signal.SIGINT, signal_handler)
print("Press Ctrl+C to exit ...")

def handle_client_connection(client_socket, address):
    print("Accepted connection from {}:{}".format(address[0], address[1]))
    try:
        while True:
            request = client_socket.recv(1024)
            if not request:
                client_socket.close()
            else:
                msg = request.decode()
                print("Received from port {} -> {}".format(address[1], msg))
                client_socket.send(("Echo -> "+msg).encode())
    except (socket.timeout, socket.error):
        print("Client {} error. Out!".format(address))




ip_addr = "0.0.0.0"
port = 8008

socketTCP = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socketTCP.bind((ip_addr, port))
socketTCP.listen(5)

print("Server Listening on {}:{}".format(ip_addr, port))

while True:
    client_socket, address = socketTCP.accept()
    client_handler = threading.Thread(target=handle_client_connection,args=(client_socket, address),daemon=True)
    client_handler.start()
