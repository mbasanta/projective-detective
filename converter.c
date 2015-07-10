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

/* convert: convert point from one projection to another*/
struct point* convert(struct point* pt, const char* inWkt, const char* outWkt) {
    GDALAllRegister();

    //const char* wgs84 = "GEOGCS[\"WGS 84\",DATUM[\"WGS_1984\",SPHEROID[\"WGS 84\",6378137,298.257223563,AUTHORITY[\"EPSG\",\"7030\"]],AUTHORITY[\"EPSG\",\"6326\"]],PRIMEM[\"Greenwich\",0,AUTHORITY[\"EPSG\",\"8901\"]],UNIT[\"degree\",0.01745329251994328,AUTHORITY[\"EPSG\",\"9122\"]],AUTHORITY[\"EPSG\",\"4326\"]]";
    //const char* nad83 = "GEOGCS[\"NAD83\",DATUM[\"North_American_Datum_1983\",SPHEROID[\"GRS 1980\",6378137,298.257222101,AUTHORITY[\"EPSG\",\"7019\"]],AUTHORITY[\"EPSG\",\"6269\"]],PRIMEM[\"Greenwich\",0,AUTHORITY[\"EPSG\",\"8901\"]],UNIT[\"degree\",0.01745329251994328,AUTHORITY[\"EPSG\",\"9122\"]],AUTHORITY[\"EPSG\",\"4269\"]]";
    //const char* nad27 = "GEOGCS[\"NAD27\",DATUM[\"North_American_Datum_1927\",SPHEROID[\"Clarke 1866\",6378206.4,294.9786982138982,AUTHORITY[\"EPSG\",\"7008\"]],AUTHORITY[\"EPSG\",\"6267\"]],PRIMEM[\"Greenwich\",0,AUTHORITY[\"EPSG\",\"8901\"]],UNIT[\"degree\",0.01745329251994328,AUTHORITY[\"EPSG\",\"9122\"]],AUTHORITY[\"EPSG\",\"4267\"]]";
    //const char* kyspn = "PROJCS[\"NAD_1983_StatePlane_Kentucky_North_FIPS_1601_Feet\",GEOGCS[\"GCS_North_American_1983\",DATUM[\"North_American_Datum_1983\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Lambert_Conformal_Conic_2SP\"],PARAMETER[\"False_Easting\",1640416.666666667],PARAMETER[\"False_Northing\",0],PARAMETER[\"Central_Meridian\",-84.25],PARAMETER[\"Standard_Parallel_1\",37.96666666666667],PARAMETER[\"Standard_Parallel_2\",38.96666666666667],PARAMETER[\"Latitude_Of_Origin\",37.5],UNIT[\"Foot_US\",0.30480060960121924],AUTHORITY[\"EPSG\",\"102679\"]]";
    //const char* kysps = "PROJCS[\"NAD_1983_StatePlane_Kentucky_South_FIPS_1602_Feet\",GEOGCS[\"GCS_North_American_1983\",DATUM[\"North_American_Datum_1983\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Lambert_Conformal_Conic_2SP\"],PARAMETER[\"False_Easting\",1640416.666666667],PARAMETER[\"False_Northing\",1640416.666666667],PARAMETER[\"Central_Meridian\",-85.75],PARAMETER[\"Standard_Parallel_1\",36.73333333333333],PARAMETER[\"Standard_Parallel_2\",37.93333333333333],PARAMETER[\"Latitude_Of_Origin\",36.33333333333334],UNIT[\"Foot_US\",0.30480060960121924],AUTHORITY[\"EPSG\",\"102680\"]]";

    struct point *returnPt = malloc(sizeof *returnPt);

    void *transformer = GDALCreateReprojectionTransformer(inWkt, outWkt);
    if (transformer == NULL) {
        return NULL;
    }

    double x[1] = { pt->x };
    double y[1] = { pt->y };
    double z[1] = { 0 };

    int projectionSuccess[1] = { FALSE };

    int success = GDALReprojectionTransform(transformer, FALSE, 1, x, y, z, projectionSuccess);
    if (success && projectionSuccess[0]) {
        returnPt->x = x[0];
        returnPt->y = y[0];
    } else {
        return NULL;
    }

    return returnPt;
}
