#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <typeinfo>

#include "Deque_MyClass.hpp"

bool compare(const MyClass& x, const MyClass& y) {
	return x.id > y.id;
}

size_t Deque_MyClass_size(Deque_MyClass* deq) {
	return deq->num_items;
}

bool Deque_MyClass_empty(Deque_MyClass* deq) {
	return deq->num_items == 0;
}

void Deque_MyClass_ctor(Deque_MyClass* deq, bool (*f)(const MyClass&, const MyClass&)) {
	deq->num_items = 0;
	//deq->type_name = "MyClass";
	//deq->type_name = { "MyClass" };
	//deq->type_name = (char*) malloc(strlen("Deque_") + strlen("MyClass") + 1); // +1 null terminator
	//strcpy(deq->type_name, "Deque_"); // strcpy() includes null terminator
	//strcat(deq->type_name, "MyClass");	
	deq->compare = f;
	
	// "methods"
	deq->size = Deque_MyClass_size;
	deq->empty = Deque_MyClass_empty;
}

void Deque_MyClass_dtor(Deque_MyClass* deq) {
	//free(deq->type_name);
}

int main() {

	printf("A Deque (non-macro version)\n");	
	Deque_MyClass deq;
	Deque_MyClass_ctor(&deq, compare);
	assert(deq.size(&deq) == 0);
	assert(typeid(std::size_t) == typeid(decltype(deq.size(&deq))));
	assert(deq.empty(&deq));

	printf("%s\n", deq.type_name);
	printf("---- %s, %d\n", deq.type_name, (int) sizeof(deq.type_name));

	Deque_MyClass_dtor(&deq);
	
	return 0;
}
