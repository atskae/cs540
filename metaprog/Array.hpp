#ifndef CS540_ARRAY_H
#define CS540_ARRAY_H

#include <tuple>
#include <exception>
#include <cassert>

#include <stdio.h>
#include <string.h>

namespace cs540 {

    // Out of range exception
    struct OutOfRange : public std::exception {
        const char* what() const throw() { return "Out of range exception."; }
    }; // struct OutOfRange

    template<typename T, size_t Dim, size_t... Dims>
    class Array {
        private:
            Array<T, Dims...> _array[Dim];
        public:
            Array() { printf("dim=%lu; sizeof(_array)=%lu\n", Dim, sizeof(_array)); }
            
            /* Copy constructor */
            
            Array(const Array<T, Dims...>& a) {
                _array = Array(a[Dim]);
                //_array[Dim] = a._array[Dim];
                //assert(false);
            }

            //template<typename U>
            //Array(const Array<U, Dims...>& a) {
            //    assert(false);
            //}

            ~Array() {}
            
            Array<T, Dims...>& operator[](int idx) {
                if(idx < 0) throw OutOfRange();
                if((size_t)idx > Dim) throw OutOfRange();

                return _array[idx];
            }

    }; // class Array

    // class Array ; base case
    template<typename T, size_t Dim>
    class Array<T, Dim> {
        private:
            T _array[Dim] = {0};
        public:
            Array() { printf("dim=%lu; sizeof(_array)=%lu\n", Dim, sizeof(_array)); }

            /* Copy constructor */
 
            Array(const Array& a) {
                printf("Base case copy constructor!\n");
                memcpy(_array, a._array, sizeof(T) * Dim);
            }

            //template<typename U>
            //Array(const Array<U, Dims...>& a) {
            //
            //}

            ~Array() {}
            
            T& operator[](int idx) {
                if(idx < 0) throw OutOfRange();
                if((size_t)idx > Dim) throw OutOfRange();

                return _array[idx];
            }
    }; // class Array ; base case

} // namespace cs540

#endif // CS540_ARRAY_H
