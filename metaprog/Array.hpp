#ifndef CS540_ARRAY_H
#define CS540_ARRAY_H

#include <tuple>
#include <stdio.h>

namespace cs540 {

    template<typename T, size_t Dim, size_t... Dims>
    class Array {
        private:
            Array<T, Dims...> _array[Dim];
        public:
            Array() { printf("dim=%lu; sizeof(_array)=%lu\n", Dim, sizeof(_array)); }
            ~Array() {}

    }; // class Array

    // recurive template ; base case
    template<typename T, size_t Dim>
    class Array<T, Dim> {
        private:
            T _array[Dim];
        public:
            Array() { printf("dim=%lu; sizeof(_array)=%lu\n", Dim, sizeof(_array)); }
            ~Array() {}
    }; // class Array

} // namespace cs540

#endif // CS540_ARRAY_H
