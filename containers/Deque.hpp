#ifndef DEQUE_H
#define DEQUE_H

#include <string.h>
#include <stdlib.h>

#define Deque_DEFINE(X)																\
	struct Deque_##X {																\
		size_t num_items;															\
		char* type_name;															\
		bool (*compare)(const X&, const X& y);										\
		size_t (*size)(Deque_##X*);													\
		bool (*empty)(Deque_##X*);													\
	};																				\
																					\
	size_t Deque_##X##_size(Deque_##X* deq) {										\
		return deq->num_items;														\
	}																				\
																					\
	bool Deque_##X##_empty(Deque_##X* deq) {										\
		return deq->num_items == 0;													\
	}																				\
																					\
	void Deque_##X##_ctor(Deque_##X* deq, bool (*f)(const X&, const X&)) {			\
		deq->num_items = 0;															\
		deq->type_name = (char*) malloc(strlen("Deque_") + strlen(#X) + 1);			\
		strcpy(deq->type_name, "Deque_");											\
		strcat(deq->type_name, #X);													\
		deq->compare = f;															\
		deq->size = Deque_##X##_size;												\
		deq->empty = Deque_##X##_empty;												\
	}																				\
																					\
	void Deque_##X##_dtor(Deque_##X* deq) {											\
		free(deq->type_name);														\
	}																				\

#endif // DEQUE_H
