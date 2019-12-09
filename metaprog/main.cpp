#include <stdio.h>

#include "Array.hpp"

int main() {
    printf("Array\n");
    cs540::Array<int, 3, 4> a;
    printf("Array<int, 3, 4>\n");
    
    int x = 1;
    int y = 2;
    a[x][y] = 14;
    printf("a[%i][%i]=%i\n", x, y, a[x][y]);
   
    // OutOfRange exception
    try {
        int num = a[100][2];
        printf("Got num=%i\n", num);
    } catch(const cs540::OutOfRange&) {
        printf("Was hat passiert?\n");
    }

    // copy constructor
    cs540::Array<int, 3, 4> b(a);
    printf("b[%i][%i]=%i\n", x, y, b[x][y]);

    printf("Aufwiedersehen.\n");
 
    return 0;
}
