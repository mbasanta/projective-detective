/**
 * main.c
 * projective-detective
 *
 * Created by Basanta, Matthew on 6/22/15.
 * Copyright (c) 2015 Matthew Basanta. All rights reserved.
 *
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libconfig.h>
#include "converter.h"
#include "point.h"
#include "comparisons.h"
#include "projective-detective.h"

double find_delta(double x1, double y1, double x2, double y2)
{
    return sqrt(pow((x2-x1), 2) + pow((y2-y1), 2));
}

struct match* find_projection(double lng, double lat, double target_x, double target_y, int count)
{

    const char* wgs84 = "GEOGCS[\"WGS 84\",DATUM[\"WGS_1984\",SPHEROID[\"WGS 84\",6378137,298.257223563,AUTHORITY[\"EPSG\",\"7030\"]],AUTHORITY[\"EPSG\",\"6326\"]],PRIMEM[\"Greenwich\",0,AUTHORITY[\"EPSG\",\"8901\"]],UNIT[\"degree\",0.01745329251994328,AUTHORITY[\"EPSG\",\"9122\"]],AUTHORITY[\"EPSG\",\"4326\"]]";

    /* Get our settings file info */
    config_t cfg;
    config_setting_t* setting;

    config_init(&cfg);
    config_set_auto_convert(&cfg, 1);

    /* Exit if there's a error with the settings file */
    if (!config_read_file(&cfg, "projections.cfg"))
    {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        return(NULL);
    }

    /* Create the list */
    ComparisonList *list;
    createNewComparisonList(&list, count);

    /* Get our projections setting */
    setting = config_lookup(&cfg, "projections");
    if (setting != NULL)
    {
        /* Create our test point */
        struct Point *pt;
        createNewPointWithVals(&pt, lng, lat);
        /* Create our target point */
        struct Point *target;
        createNewPointWithVals(&target, target_x, target_y);

        int count = config_setting_length(setting);
        int i;
        for (i = 0; i < count; ++i) {
            config_setting_t* projection = config_setting_get_elem(setting, i);
            const char* wkt;
            const char* name;
            const char* unit;
            double unit_factor;
            int epsg;

            if (!(config_setting_lookup_string(projection, "wkt", &wkt)
                  && config_setting_lookup_string(projection, "name", &name)
                  && config_setting_lookup_string(projection, "unit", &unit)
                  && config_setting_lookup_float(projection, "unit_factor", &unit_factor)
                  && config_setting_lookup_int(projection, "epsg", &epsg)))
            {
                fprintf(stderr, "Incomplete projection\n\n");
                continue;
            }

            struct Point *newPt = NULL;
            convert(&pt, &newPt, wgs84, wkt);
            if (newPt != NULL)
            {
                double delta = find_delta(target->x, target->y, newPt->x, newPt->y) * unit_factor;

                /* Create our memory to hold the comparisons */
                Comparison *comparison;

                createNewComparisonWithVals(&comparison, unit_factor, delta, (char*) name);
                addComparisonToList(&list, comparison);

                destroyPoint(&newPt);
                destroyComparison(&comparison);
            }
            else
            {
                /* printf("error on %s...\n", name); */
            }

        }

        destroyPoint(&pt);
        destroyPoint(&target);
    }

    /* Clean up Config data */
    config_destroy(&cfg);

    struct match *returnList = malloc(list[0].size * sizeof(match));

    unsigned long i;
    for (i = 0; i < list[0].size; i++) {
        Comparison *comp = getComparisonByIndex(&list, i);
        if (comp) {
            returnList[i].projection = comp->projection;
            returnList[i].delta = comp->delta;
        }
    }

    destroyComparisonList(&list);

    return returnList;
}
