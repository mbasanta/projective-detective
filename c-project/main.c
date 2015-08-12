/**
 * main.c
 * projective-detective
 *
 * Created by Basanta, Matthew on 6/22/15.
 * Copyright (c) 2015 Matthew Basanta. All rights reserved.
 *
 */

#include <stdio.h>
#include "projective-detective.h"

int main() {

    match *matches = find_projection(-84.123, 38.456, 511084, 106120.999999, 10);

    for (int i = 0; i < 10; i++) {
        printf("Comp %u -- %s (%f)\n", i, matches[i].projection, matches[i].delta);
    }

    return 0;
}
