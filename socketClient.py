import socket # for socket
import sys
  
try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print ("Socket successfully created")
except socket.error as err:
    print ("socket creation failed with error %s" %(err))
  
# default port for socket
port = 10000

host_ip = "10.23.11.53"
  
# connecting to the server
s.connect((host_ip, port))
  
print ("the socket has successfully connected to google \
on port == %s" %(host_ip))

while(True):
    data = input()
    s.send(data.encode())
