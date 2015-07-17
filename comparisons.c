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

void addComparisonToList(ComparisonList ** list, Comparison * comparison)
{
    Comparison *comparisonToAdd;
    createNewComparisonWithVals(&comparisonToAdd,
            comparison->unit_factor, comparison->delta, comparison->projection);

    if ((*list)->size >= (*list)->maxSize) {
        /* Make sure we have something to work with */
        if ((*list)->comparisons[0] == NULL) { return; }

        int largestIndex = -1;
        double largestDelta = comparison->delta;
        /* Loop through the rest of the list */
        for (unsigned long i = 0; i < (*list)->size; i++) {
            if ((*list)->comparisons[i]->delta > largestDelta) {
                largestIndex = i;
                largestDelta = (*list)->comparisons[i]->delta;
            }
        }

        /* If we have a larger delta, replace it */
        if (largestIndex >= 0) {
            (*list)->comparisons[largestIndex] = comparisonToAdd;
        } else {
            destroyComparison(&comparisonToAdd);
        }
    } else {
        int newComparisonCount = (*list)->size + 1;
        size_t newSize = newComparisonCount * sizeof(Comparison *);
        Comparison ** newComparisons = realloc((*list)->comparisons, newSize);

        if (newComparisons == NULL) { return; }

        (*list)->size = newComparisonCount;
        (*list)->comparisons = newComparisons;
        (*list)->comparisons[newComparisonCount - 1] = comparisonToAdd;
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
