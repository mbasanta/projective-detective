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
    (*list)->size = 1;
    (*list)->comparisons = malloc((*list)->size * sizeof(Comparison *));
    /* Initialize new structs */
    unsigned long i;
    for (i = 0; i < (*list)->size; i++) {
        (*list)->comparisons[i] = NULL;

    }
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
    (*list)->comparisons[1] = *comparison;
}

Comparison * addNewComparisonToList(ComparisonList * list)
{
    int newComparisonCount = list->size + 1;
    size_t newSize = newComparisonCount * sizeof(Comparison *);
    Comparison ** newComparison = realloc(list->comparisons, newSize);
    if (newComparison != NULL) {
        list->size = newSize;
        list->comparisons = newComparison;
        createNewComparison(&(newComparison[newComparisonCount - 1]));
        return newComparison[newComparisonCount -1];
    }
    return NULL;
}

Comparison *getComparisonByIndex(ComparisonList ** list, int index)
{
    if ((unsigned long)index >= (*list)->size)
    {
        return NULL;
    }

    return (*list)->comparisons[index];
}
