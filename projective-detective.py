#!/usr/local/bin/python

import ogr, osr
import datetime

print "Start: ", datetime.datetime.now()

for i in range(10000):
    pointX = -84
    pointY = 38

    inputESPG = 4267
    outputEPSG = 2246

    point = ogr.Geometry(ogr.wkbPoint)
    point.AddPoint(pointX, pointY)

    inSpatialRef = osr.SpatialReference()
    inSpatialRef.ImportFromEPSG(inputESPG)

    outSpatialRef = osr.SpatialReference()
    outSpatialRef.ImportFromEPSGA(outputEPSG)

    coordTransform = osr.CoordinateTransformation(inSpatialRef, outSpatialRef)

    point.Transform(coordTransform)

print "end: ", datetime.datetime.now()
print point.GetX(), point.GetY()
