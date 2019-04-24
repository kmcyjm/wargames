#!/usr/bin/env python

'''
Level Goal
Your goal is to connect to port 5842 on vortex.labs.overthewire.org and read in 4 unsigned integers in host byte order. Add these integers together and send back the results to get a username and password for vortex1. This information can be used to log in using SSH.

Note: vortex is on an 32bit x86 machine (meaning, a little endian architecture)
'''
# code from geohot

import socket
import struct
import telnetlib

#HOST = 'vortex.labs.overthewire.org'
#PORT = 5842
HOST = 'localhost'
PORT = 7890

def q(a):
    # struct.pack() convert python value to c struct
    return struct.pack("I", a)

def interact():
    print(" ** INTERACT ** ")
    t = telnetlib.Telnet()
    t.sock = s
    t.interact()

s = socket.create_connection((HOST, PORT))

#acc = 0
#
#for i in range(4):
#    # unpack() returns a tuple even if only one element there
#    acc += struct.unpack("I", s.recv(4))[0]
#
#s.send(q(acc))

interact()
