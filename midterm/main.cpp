#include <stdio.h>
#include <string.h>

#include "String.hpp"

int main() {
    
    const char* test = "hallo";
    cs540::String s1(test);
    cs540::String s2(test);
    cs540::String s3 = s1 + s2;
    s3.print();

    return 0;
}
