/**
 * main.c
 * projective-detective
 *
 * Created by Basanta, Matthew on 6/22/15.
 * Copyright (c) 2015 Matthew Basanta. All rights reserved.
 *
 */

#ifndef PROJECTIVEDETECTIVE_H
#define PROJECTIVEDETECTIVE_H

typedef struct match {
    char* projection;
    double delta;
} match;

struct match* find_projection(double lng, double lat, double target_x, double target_y, int count);

#endif
