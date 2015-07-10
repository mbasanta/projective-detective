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

double find_delta(int x1, int y1, int x2, int y2)
{
    return sqrt(pow((x2-x1), 2) + pow((y2-y1), 2));
}

int main() {

    const char* wgs84 = "GEOGCS[\"WGS 84\",DATUM[\"WGS_1984\",SPHEROID[\"WGS 84\",6378137,298.257223563,AUTHORITY[\"EPSG\",\"7030\"]],AUTHORITY[\"EPSG\",\"6326\"]],PRIMEM[\"Greenwich\",0,AUTHORITY[\"EPSG\",\"8901\"]],UNIT[\"degree\",0.01745329251994328,AUTHORITY[\"EPSG\",\"9122\"]],AUTHORITY[\"EPSG\",\"4326\"]]";

    config_t cfg;
    config_setting_t* setting;

    config_init(&cfg);
    config_set_auto_convert(&cfg, 1);

    /* Exit if there's a error */
    if (!config_read_file(&cfg, "projections.cfg"))
    {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        return(EXIT_FAILURE);
    }

    setting = config_lookup(&cfg, "projections");
    if (setting != NULL)
    {
        /* Create our test point */
        struct point *pt = malloc(sizeof *pt);
        pt->x = -84;
        pt->y = 38;

        struct point *target = malloc(sizeof *target);
        target->x = 5425460;
        target->y = 3892419.8;

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

            /* printf("wkt -- %s\n\n", wkt); */

            struct point *newPt = convert(pt, wgs84, wkt);
            double delta = find_delta(target->x, target->y, newPt->x, newPt->y) * unit_factor;

            /* printf("Input -- x: %f, y: %f\n", pt->x, pt->y); */
            /* printf("Output -- x: %f, y: %f\n", newPt->x, newPt->y); */
            printf("%s delta = %lf\n", name, delta);

            free(newPt);
        }

        free(pt);
        free(target);
    }

    return 0;
}