#!/usr/local/bin/python

'''Tester for converting points'''

# pylint: disable=too-few-public-methods

import ctypes
import datetime
import os

lib = os.path.join(os.path.dirname(os.path.realpath(__file__)), "projective-detective.so")

class Point(ctypes.Structure):
    '''Python class to mirror point struct in c'''
    _fields_ = [("x", ctypes.c_double),
                ("y", ctypes.c_double)]

class Match(ctypes.Structure):
    '''Python class to mirror match struct in c'''
    _fields_ = [("projection", ctypes.c_char_p),
                ("delta", ctypes.c_double)]

def convert_point():
    '''Main tester function'''
    start = datetime.datetime.now()

    #cdll.LoadLibrary("converter.so")
    proj_detective = ctypes.CDLL(lib)
    proj_detective.find_projection.restype = ctypes.POINTER(Match)
    proj_detective.find_projection.argtypes = [
        ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_int]

    ret_val = proj_detective.find_projection(-84, 38, 1712479.21678, 182207.371943, 5)

    end = datetime.datetime.now()
    elapsed = datetime.timedelta = end - start
    print elapsed

    for i in range(5):
        print ret_val[i].projection + "(Delta: " + str(ret_val[i].delta) + ")"
    # print 'x: ' + str(ret_val.contents.x)
    # print 'y: ' + str(ret_val.contents.y)

if __name__ == '__main__':
    convert_point()
