/**
 * comparisons.c
 * projective-detective
 *
 * Created by Basanta, Matthew on 7/10/15.
 * Copyright (c) 2015 Matthew Basanta. All rights reserved.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "comparisons.h"

void createNewComparison(Comparison ** comparison)
{
    (*comparison) = malloc(sizeof(Comparison));
    (*comparison)->unit_factor = 0;
    (*comparison)->delta = 0;
    (*comparison)->projection = NULL;
}

void createNewComparisonWithVals(Comparison ** comparison,
        double unit_factor, double delta, char* projection)
{
    (*comparison) = malloc(sizeof(Comparison));
    (*comparison)->unit_factor = unit_factor;
    (*comparison)->delta = delta;
    (*comparison)->projection = projection;
}

void destroyComparison(Comparison ** comparison)
{
    if ((*comparison) != NULL) {
        /*
        if((*comparison)->projection != NULL) {
            free((*comparison)->projection);
        }
        */
        free((*comparison));
    }
}

void createNewComparisonList(ComparisonList ** list, int size)
{
    /* Create new list */
    (*list) = malloc(sizeof(ComparisonList));
    /* Create a new list of struct pointers */
    (*list)->maxSize = size;
    (*list)->size = 0;
    (*list)->comparisons = NULL;
}

void destroyComparisonList(ComparisonList ** list)
{
    /* Destroy each struct */
    unsigned long i;
    for (i = 0; i < (*list)->size; i++) {
        destroyComparison(&((*list)->comparisons[i]));
    }
}

void addComparisonToList(ComparisonList ** list, Comparison ** comparison)
{
    int newComparisonCount = (*list)->size + 1;
    size_t newSize = newComparisonCount * sizeof(Comparison *);
    Comparison ** newComparison = realloc((*list)->comparisons, newSize);

    if (newComparison == NULL) { return; }

    if ((*list)->size >= (*list)->maxSize) {
        printf("size is greater than or equal to maxSize\n");
    } else {
        printf("size is less than maxSize\n");
        (*list)->size = newComparisonCount;
        (*list)->comparisons = newComparison;
        (*list)->comparisons[newComparisonCount - 1] = *comparison;
    }
}

Comparison *getComparisonByIndex(ComparisonList ** list, int index)
{
    if ((unsigned long)index >= (*list)->size)
    {
        return NULL;
    }

    return (*list)->comparisons[index];
}
