/**
 * comparisons.h
 * projective-detective
 *
 * Created by Basanta, Matthew on 7/10/15.
 * Copyright (c) 2015 Matthew Basanta. All rights reserved.
 *
 */

#ifndef COMPARISONS_H
#define COMPARISONS_H

#include <stdlib.h>

typedef struct Comparison {
    char *projection;
    double unit_factor;
    double delta;
} Comparison;

typedef struct ComparisonList {
    Comparison **comparisons;
    size_t size;
    size_t maxSize;
} ComparisonList;

void createNewComparison(Comparison ** comparison);

void createNewComparisonWithVals(Comparison ** comparison,
        double unit_factor, double delta, char* projection);

void destroyComparison(Comparison ** comparison);

void createNewComparisonList(ComparisonList ** list, int size);

void destroyComparisonList(ComparisonList ** list);

/* void addComparisonToList(ComparisonList ** list, Comparison ** comparison); */

Comparison * addNewComparisonToList(ComparisonList * list);

Comparison *getComparisonByIndex(ComparisonList ** list, int index);

#endif
