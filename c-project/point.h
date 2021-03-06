/**
 * point.h
 * projective-detective
 *
 * Created by Basanta, Matthew on 7/10/15.
 * Copyright (c) 2015 Matthew Basanta. All rights reserved.
 *
 */

#ifndef POINT_H
#define POINT_H

struct Point {
    double x;
    double y;
};

static const struct Point EMPTYPOINT;

void createNewPointWithVals(struct Point ** newPoint, double x, double y);

void destroyPoint(struct Point ** point);

#endif
