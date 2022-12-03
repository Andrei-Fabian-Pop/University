# #!/usr/bin/python
# #cli
#
# import socket, select
#
# host = '121.40.77.208'
# port = 10000
#
# socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# socket.connect((host, port))
# inout = [socket]
#
# while 1:
#     infds, outfds, errfds = select.select(inout, inout, [], 5)
#     if len(infds) != 0:
#         buf = socket.recv(1024)
#         if len(buf) != 0:
#             print
#             'receive data:', buf
#     if len(outfds) != 0:
#         socket.send("python select client from Debian.\n")
#
# # serv
# # !/usr/bin/python
#
# import socket, select
#
# host = ''
# port = 10000
#
# socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# socket.bind((host, port))
# socket.listen(5)
# inputs = [socket]
#
# while 1:
#     infds, outfds, errfds = select.select(inputs, inputs, [], 5)
#     if len(infds) != 0:
#         # print 'enter infds'
#         for fds in infds:
#             if fds is socket:
#                 clientsock, clientaddr = fds.accept()
#                 inputs.append(clientsock)
#                 # print 'connect from:', clientaddr
#             else:
#                 # print 'enter data recv'
#                 data = fds.recv(1024)
#
#                 if not data:
#                     inputs.remove(fds)
#                 else:
#                     print
#                     data
#
#     if len(outfds) != 0:
#         # print 'enter outfds'
#         for fds in outfds:
#             fds.send("python select server from Debian.\n")
