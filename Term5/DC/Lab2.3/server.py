import socket

from database import Database
from message import *

host = socket.gethostname()
port = 3600

s = socket.socket()
s.bind((host, port))

db = Database()

print("Waiting for client")
while True:
    s.listen()
    c, addr = s.accept()
    print(addr, " Connected")

    try:
        while True:
            data = c.recv(256)
            msg = Message.unpack(data)

            r = "Success"
            try:
                if msg.cmd == "adda": db.add_airline(*msg.args)
                elif msg.cmd == "rema": db.remove_airline(*msg.args)
                elif msg.cmd == "upda": db.update_airline(*msg.args)
                elif msg.cmd == "addf": db.add_flight(*msg.args)
                elif msg.cmd == "remf": db.remove_flight(*msg.args)
                elif msg.cmd == "updf": db.update_flight(*msg.args)

                elif msg.cmd == "geta": r = db.get_airline(*msg.args)
                elif msg.cmd == "getf": r = db.get_flight(*msg.args)
                elif msg.cmd == "lsa": r = db.get_airlines()
                elif msg.cmd == "lsf": r = db.get_flights()
            except Exception as e:
                r = str(e)

            print(msg, ":", r)
            c.send(pickle.dumps(r))

    except EOFError:
        print(addr, " Disconnected")
    except:
        print("Some Error")

