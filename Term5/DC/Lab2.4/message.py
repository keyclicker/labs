import pickle


class Message:
    def __init__(self, cmd, *args):
        self.cmd = cmd
        self.args = args

    @staticmethod
    def unpack(data):
        obj = pickle.loads(data)
        return Message(obj.cmd, *obj.args)

    def pack(self):
        return pickle.dumps(self)

    def __str__(self):
        return self.cmd + " " + str(self.args)

