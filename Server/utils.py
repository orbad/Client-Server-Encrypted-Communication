""" Name: Or Badani """

from constants import *
import os

def getPort(filename):
    """
    Gets the port from the file.
    If file doesn't exist, defaults to port 1357. 
    """

    port = DEFAULT_PORT
    try:
        with open(filename) as f:
            readPort = f.readline().strip()
            port = int(readPort)
    except Exception as e:
        print(f'Error opening file: {e}')
    return port


def sendPacket(socket, buffer):
    """ The function pads the buffer with \0 and sends it over the socket. """
    if len(buffer) < PACKET_SIZE:
        buffer += bytearray(PACKET_SIZE - len(buffer))  # Pad with \0

    socket.send(buffer)


def createDirectory(directory):
    """ If directory doesn't exist, it is created. """
    if not os.path.exists(directory):
        os.mkdir(directory)
