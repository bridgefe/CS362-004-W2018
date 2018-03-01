#include "simpleAssert.h"
#include <stdio.h>



void ass(int a, int b) {
    if (a == b) {
        printf("Test: PASSED\n");
    }
    else {
        printf("Test: FAILED\n");
    }
}
