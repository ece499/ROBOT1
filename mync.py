import socket
import sys

def mync(adder,port):
	ap=(str(adder),int(port))
	s=socket.socket()
	s.connect(ap)
	try:
		while(True):
			cmd=raw_input(s.recv(0x8000))
			s.sendall(cmd)
	except:
		s.close()

	
if __name__=="__main__":
	mync(sys.argv[1],sys.argv[2])
