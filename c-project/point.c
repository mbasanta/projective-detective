/**
 * point.c
 * projective-detective
 *
 * Created by Basanta, Matthew on 7/10/15.
 * Copyright (c) 2015 Matthew Basanta. All rights reserved.
 *
 */

#include <stdlib.h>
#include "point.h"

void createNewPointWithVals(struct Point ** newPoint, double x, double y)
{
    (*newPoint) = malloc(sizeof(struct Point));
    (*newPoint)->x = x;
    (*newPoint)->y = y;
}

void destroyPoint(struct Point ** point)
{
    if ((*point) != NULL) {
        free((*point));
    }
}
