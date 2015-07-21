/**
 * converter.c
 * projective-detective
 *
 * Created by Basanta, Matthew on 6/22/15.
 * Copyright (c) 2015 Matthew Basanta. All rights reserved.
 *
 */

#include <gdal_alg.h>
#include "converter.h"
#include "point.h"

/* convert: convert point from one projection to another*/
struct Point* convert(struct Point* pt, const char* inWkt, const char* outWkt) {
    /* GDALAllRegister(); */

    void *transformer = GDALCreateReprojectionTransformer(inWkt, outWkt);
    if (transformer == NULL) {
        return NULL;
    }

    double x[1] = { pt->x };
    double y[1] = { pt->y };
    double z[1] = { 0 };

    int projectionSuccess[1] = { FALSE };

    struct Point *returnPt = newPoint(0, 0);
    int success = GDALReprojectionTransform(transformer, FALSE, 1, x, y, z, projectionSuccess);
    GDALDestroyReprojectionTransformer(transformer);

    if (success && projectionSuccess[0]) {
        returnPt->x = x[0];
        returnPt->y = y[0];
    } else {
        return NULL;
    }

    return returnPt;
}
