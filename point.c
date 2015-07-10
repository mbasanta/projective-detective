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

struct Point *newPoint (double x, double y)
{
    struct Point *retVal = malloc (sizeof (struct Point));
    if (retVal == NULL) {
        return NULL;
    }

    retVal->x = x;
    retVal->y = y;

    return retVal;
}

void delPoint (struct Point *point)
{
    if (point != NULL) {
        free(point);
    }
}
