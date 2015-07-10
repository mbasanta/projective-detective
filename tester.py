#!/usr/local/bin/python

'''Tester for converting points'''

# pylint: disable=too-few-public-methods

import ctypes

class Point(ctypes.Structure):
    '''Python class to mirror point struct in c'''
    _fields_ = [("x", ctypes.c_double),
                ("y", ctypes.c_double)]

def convert_point():
    '''Main tester function'''
    point = Point(-84, 38)

    #cdll.LoadLibrary("converter.so")
    converter = ctypes.CDLL("converter.so")
    converter.convert.restype = ctypes.POINTER(Point)

    ret_val = converter.convert(ctypes.byref(point))

    print 'x: ' + str(ret_val.contents.x)
    print 'y: ' + str(ret_val.contents.y)

if __name__ == '__main__':
    convert_point()
