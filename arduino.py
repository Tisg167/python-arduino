import serial
#import json
import ast

class Arduino:
    def __init__(self, dev='/dev/ttyACM0', baud=9600):
        self.port = serial.Serial(dev, baud)

    def listen(self):
        self.port.flush()
        s = self.port.readline()
        return s

    def parse(self, s):
        try:
            msg = ast.literal_eval(s)
            print msg
            d = msg['data']
            return d
        except:
            return None

if __name__ == '__main__':
    app = Arduino()
    while True:
        a = app.listen()
        res = app.parse(a)
        print res
