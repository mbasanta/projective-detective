/**
 * converter.h
 * projective-detective
 *
 * Created by Basanta, Matthew on 6/22/15.
 * Copyright (c) 2015 Matthew Basanta. All rights reserved.
 *
 */

#ifndef CONVERTER_H
#define CONVERTER_H

#include "point.h"

void convert(struct Point ** pt, struct Point ** newPt, const char* inWkt, const char* outWkt);

#endif
