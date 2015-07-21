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

    match *matches = find_projection(-84, 38, 5425460, 3892419.8, 5);

    for (int i = 0; i < 5; i++) {
        printf("Comp %u -- %s (%f)\n", i, matches[i].projection, matches[i].delta);
    }

    return 0;
}
