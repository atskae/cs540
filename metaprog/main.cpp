#include <stdio.h>

#include "Array.hpp"

int main() {
    printf("Array\n");
    cs540::Array<int, 3, 4> a;
    printf("sizeof(int)=%lu\n", sizeof(int));
    return 0;
}
