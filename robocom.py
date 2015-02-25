import serial
import socket
import sys

def robocom(port=2222,serport="/dev/ttyACM0")
        s=socket.socket()
        s.bind(('',port))
        s.listen(1)
        cs,address=s.accept()
        ser=serial.Serial(serport,9600)
        try:
                while True:
                        cs.sendall("cmd s l r b f> ")
                        cmd=cs.recv(5)
                        ser.write(str(cmd))
        except:
                s.close()
                cs.close()


if __name__=="__main__":
        if len(sys.argv==3):
                robocom(sys.argv[1],sys.argv[2])
        elif len(sys.argv==2):
                robocom(sys.argv[1])
        else:
                robocom()
