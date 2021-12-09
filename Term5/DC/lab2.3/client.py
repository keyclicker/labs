import socket
from message import *

host = socket.gethostname()
port = 3600

s = socket.socket()

s.connect((host, port))


def _exec(cmd, *args):
    s.send(Message(cmd, *args).pack())
    return pickle.loads(s.recv(256))


# exec and log
def eal(cmd, *args):
    print(cmd, args, ":", _exec(cmd, *args))


eal("adda", 50, "Name", "City")
eal("addf", 98, 50, "From", "To")

print()
eal("upda", 50, "Edited Name", "City")
eal("updf", 98, "From", "To EDIT")

print()
eal("geta", 50)
eal("getf", 98)

print()
eal("rema", 50)
eal("remf", 98)

print()
eal("lsa")
eal("lsf")


