#include <stdio.h>
#include <typeinfo>
#include <assert.h>

#include "Deque.hpp"

struct MyClass {
	int id;
	char* name;
};

bool compare_int(const int& x, const int& y) {
	return x > y;
}

bool compare(const MyClass& x, const MyClass& y) {
	return x.id > y.id;
}

Deque_DEFINE(int)
Deque_DEFINE(char)
Deque_DEFINE(MyClass)

int main() {

	printf("Containers in C: Deque\n");	
	
	Deque_int d_int;
	Deque_char d_char;
	Deque_MyClass deq;

	Deque_MyClass_ctor(&deq, compare);

	Deque_int_ctor(&d_int, compare_int);
	Deque_int_dtor(&d_int);

	printf("size=%lu\n", deq.size(&deq));
	assert(typeid(std::size_t) == typeid(decltype(deq.size(&deq))));
	assert(deq.empty(&deq));

	printf("%s\n", deq.type_name);
	printf("---- %s, %d\n", deq.type_name, (int) sizeof(deq.type_name));

	Deque_MyClass_dtor(&deq);

	return 0;
}
