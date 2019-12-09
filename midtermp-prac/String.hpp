#ifndef CS540_STRING_H
#define CS540_STRING_H

#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h>

namespace cs540 {
    
    class String {
        private:
            char* _str;
            int _len;
        public:
            String(const char* str) : _str(nullptr), _len(0) {
                _len = strlen(str);
                _str = (char*) malloc(_len + 1); // +1 for null terminator
                strcpy(_str, str);
                _str[_len] = 0; // null terminator
            }

            //String operator+(const String& s) {
            //    _len = _len + s.length();
            //    _str = (char*) realloc(_len + 1); // +1 null terminator
            //    strcat(_str, s.getCharPtr());
            //}

            friend String operator+(const String& s1, const String& s2) {
                char* str = (char*) malloc(s1._len + s2._len + 1); // +! null terminator
                strcpy(str, s1._str);
                strcat(str, s2._str);
                String s(str);
                free(str);
                
                return s;
            }

            int length() const {
                return _len;
            }

            void print() {
                for(int i=0; i<_len; i++) {
                    printf("%c", _str[i]);
                }
                printf("\n");
            }

            ~String() {
                free(_str);
            }

    }; // class String

} // namespace cs540

#endif // CS540_STRING_H
