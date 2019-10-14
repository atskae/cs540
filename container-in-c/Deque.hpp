#ifndef DEQUE_H
#define DEQUE_H

#include <string.h>
#include <stdlib.h>

#define DEQUE_INIT_SIZE 4

#define Deque_DEFINE(X)																					\
																										\
	struct Deque_##X;																					\
																										\
	struct Deque_##X##_Iterator {																		\
		Deque_##X* deq;																					\
		int index;																						\
		int num_to_end;																					\
																										\
		void (*inc)(Deque_##X##_Iterator*); 															\
		void (*dec)(Deque_##X##_Iterator*); 															\
		X& (*deref)(Deque_##X##_Iterator*);																\
	};																									\
																										\
	bool Deque_##X##_Iterator_equal(Deque_##X##_Iterator it1, Deque_##X##_Iterator it2); 				\
																										\
	struct Deque_##X {																					\
		size_t num_items;																				\
		char type_name[sizeof "Deque_"#X];																\
		X* deque;																						\
		int front_ptr;																					\
		int back_ptr;																					\
		size_t max_items;																				\
																										\
		bool (*compare)(const X&, const X& y);															\
																										\
		void (*dtor)(Deque_##X*);																		\
		size_t (*size)(Deque_##X*);																		\
		bool (*empty)(Deque_##X*);																		\
		void (*push_back)(Deque_##X*, const X);															\
		void (*push_front)(Deque_##X*, const X);														\
		X& (*front)(Deque_##X*);																		\
		X& (*back)(Deque_##X*);																			\
		void (*pop_front)(Deque_##X*);																	\
		void (*pop_back)(Deque_##X*);																	\
		void (*clear)(Deque_##X* deq);																	\
		void (*sort)(Deque_##X* deq, Deque_##X##_Iterator front, Deque_##X##_Iterator end);				\
																										\
		Deque_##X##_Iterator (*begin)(Deque_##X*);														\
		Deque_##X##_Iterator (*end)(Deque_##X*);														\
		X& (*at)(Deque_##X* deq, int from_front);														\
																										\
		void (*double_max_items)(Deque_##X*);															\
	};																									\
																										\
	X& Deque_##X##_Iterator_deref(Deque_##X##_Iterator* it) {											\
		return it->deq->deque[it->index];																\
	}																									\
																										\
	void Deque_##X##_Iterator_inc(Deque_##X##_Iterator* it) {											\
		if(it->num_to_end == 0) return;																	\
		it->index--;																					\
		if(it->index < 0) it->index = it->deq->max_items - 1;											\
		it->num_to_end--;																				\
	}																									\
																										\
	void Deque_##X##_Iterator_dec(Deque_##X##_Iterator* it) {											\
		it->index = (it->index + 1) % it->deq->max_items;												\
		it->num_to_end++;																				\
	}																									\
																										\
	Deque_##X##_Iterator Deque_##X##_end(Deque_##X* deq) {												\
		Deque_##X##_Iterator it;																		\
		it.deq = deq;																					\
		it.index = deq->back_ptr;																		\
		it.num_to_end = 0;																				\
																										\
		it.inc = Deque_##X##_Iterator_inc;																\
		it.dec = Deque_##X##_Iterator_dec;																\
		it.deref = Deque_##X##_Iterator_deref;															\
		return it;																						\
	}																									\
																										\
	Deque_##X##_Iterator Deque_##X##_begin(Deque_##X* deq) {											\
		if(deq->num_items == 0) return deq->end(deq);													\
		Deque_##X##_Iterator it;																		\
		it.deq = deq;																					\
		if(deq->front_ptr == 0) it.index = deq->max_items - 1;											\
		else it.index = deq->front_ptr - 1;																\
		it.num_to_end = deq->num_items; 																\
																										\
		it.inc = Deque_##X##_Iterator_inc;																\
		it.dec = Deque_##X##_Iterator_dec;																\
		it.deref = Deque_##X##_Iterator_deref;															\
		return it;																						\
	}																									\
																										\
	bool Deque_##X##_Iterator_equal(Deque_##X##_Iterator it1, Deque_##X##_Iterator it2) { 				\
		return (it1.index == it2.index) && (it1.num_to_end == it2.num_to_end);							\
	}																									\
																										\
	size_t Deque_##X##_size(Deque_##X* deq) {															\
		return deq->num_items;																			\
	}																									\
																										\
	bool Deque_##X##_empty(Deque_##X* deq) {															\
		return deq->num_items == 0;																		\
	}																									\
																										\
	X& Deque_##X##_at(Deque_##X* deq, int from_front) {													\
		assert(from_front >= 0);																		\
		assert((size_t)from_front < deq->num_items);													\
		int idx = deq->front_ptr; 																		\
		idx--;																							\
		if(idx < 0) idx = deq->max_items - 1;															\
																										\
		if(idx - from_front < 0) idx = (deq->max_items - (from_front - idx));							\
		else idx = idx - from_front;																	\
																										\
		return deq->deque[idx];																			\
	}																									\
																										\
	void Deque_##X##_double_max_items(Deque_##X* deq) {													\
		assert(deq->num_items == deq->max_items);														\
		size_t deq_old_size = deq->max_items;															\
		deq->max_items *= 2;																			\
		deq->deque = (X*) realloc(deq->deque, deq->max_items * sizeof(X));								\
		int new_back_ptr = deq->max_items - 1;															\
		int lower_bound = deq->back_ptr;																\
		assert(lower_bound >=0);																		\
		if((size_t)lower_bound == deq_old_size-1) lower_bound = -1;										\
		for(int i=deq_old_size-1; i>lower_bound; i--) {													\
			deq->deque[new_back_ptr] = deq->deque[i];													\
			new_back_ptr--;																				\
		}																								\
		deq->back_ptr = new_back_ptr;																	\
	}																									\
																										\
	void Deque_##X##_push_back(Deque_##X* deq, const X m) {												\
		if(deq->num_items == deq->max_items) {															\
			deq->double_max_items(deq);																	\
		}																								\
																										\
		deq->deque[deq->back_ptr] = m;																	\
		deq->back_ptr--;																				\
		if(deq->back_ptr < 0) deq->back_ptr = deq->max_items - 1;										\
		deq->num_items++;																				\
	}																									\
																										\
	void Deque_##X##_push_front(Deque_##X* deq, const X m) {											\
		if(deq->num_items == deq->max_items) {															\
			deq->double_max_items(deq);																	\
		}																								\
																										\
		deq->deque[deq->front_ptr] = m;																	\
		deq->front_ptr = (deq->front_ptr + 1) % deq->max_items;											\
		deq->num_items++;																				\
	}																									\
																										\
	X& Deque_##X##_front(Deque_##X* deq) {																\
		int ptr = deq->front_ptr - 1;																	\
		if(ptr < 0) ptr = deq->max_items - 1;															\
		return deq->deque[ptr];																			\
	}																									\
																										\
	X& Deque_##X##_back(Deque_##X* deq) {																\
		int ptr = deq->back_ptr + 1;																	\
		if((size_t)ptr == deq->max_items) ptr = 0;														\
		return deq->deque[ptr];																			\
	}																									\
																										\
	void Deque_##X##_pop_front(Deque_##X* deq) {														\
		if(deq->num_items == 0) return;																	\
																										\
		deq->front_ptr--;																				\
		if(deq->front_ptr < 0) deq->front_ptr = deq->max_items - 1;										\
		deq->num_items--;																				\
																										\
		if(deq->empty(deq)) {																			\
			deq->front_ptr = 0;																			\
			deq->back_ptr = deq->max_items - 1;															\
		}																								\
	}																									\
																										\
	void Deque_##X##_pop_back(Deque_##X* deq) {															\
		if(deq->num_items == 0) return;																	\
																										\
		deq->back_ptr = (deq->back_ptr + 1) % deq->max_items;											\
		deq->num_items--;																				\
																										\
		if(deq->empty(deq)) {																			\
			deq->front_ptr = 0;																			\
			deq->back_ptr = deq->max_items - 1;															\
		}																								\
	}																									\
																										\
	void Deque_##X##_clear(Deque_##X* deq) {															\
		if(deq->num_items == 0) return;																	\
		deq->num_items = 0;																				\
		deq->front_ptr = 0;																				\
		deq->back_ptr = deq->max_items - 1;																\
	}																									\
																										\
	void Deque_##X##_swap(X* array, int i, int j) {                                         			\
		X temp = array[i];                                                                  			\
		array[i] = array[j];                                                                			\
		array[j] = temp;                                                                    			\
	}                                                                                       			\
	                                                                                        			\
	int Deque_##X##_partition(X* array, bool (*compare)(const X&, const X&), int b, int f) {			\
		X pivot = array[f];																				\
		int i = b-1;                                                                        			\
		for(int j=b; j<=f-1; j++) {                                                         			\
			if(!compare(array[j], pivot)) {                                                 			\
				i++;                                                                        			\
				Deque_##X##_swap(array, i, j);                                              			\
			}                                                                               			\
		}                                                                                   			\
		Deque_##X##_swap(array, i+1, f);                                                    			\
		return i+1;                                                                         			\
	}																									\
																										\
	void Deque_##X##_quicksort(X* array, bool (*compare)(const X&, const X&), int b, int f) {			\
		if(b < f) {																						\
			int pi = Deque_##X##_partition(array, compare, b, f);										\
			Deque_##X##_quicksort(array, compare, b, pi-1);												\
			Deque_##X##_quicksort(array, compare, pi+1, f);												\
		}																								\
	}																									\
																										\
	void Deque_##X##_sort(Deque_##X* deq, Deque_##X##_Iterator front, Deque_##X##_Iterator end) {		\
		if(deq->num_items <= 1) return;																	\
																										\
		int bi = (end.index + 1) % deq->max_items;														\
		int fi = front.index;																			\
																										\
		if(deq->front_ptr <= deq->back_ptr) {                                                           \
			assert(deq->back_ptr >= 0);                                                                 \
			if(deq->num_items != deq->max_items && (size_t) deq->back_ptr != deq->max_items - 1) {      \
				X* temp_array = (X*) malloc(deq->num_items * sizeof(X));              					\
				int num_back = deq->max_items - deq->back_ptr - 1;                                      \
																										\
				int b = (deq->back_ptr + 1) % deq->max_items;											\
				for(int i=0; i<num_back; i++) {                                                         \
					temp_array[i] = deq->deque[b];                                                     	\
					b = (b + 1) % deq->max_items;                                                     	\
				}                                                                                       \
				int f = 0;																				\
				for(int i=0; i<deq->front_ptr; i++) {                                                   \
					temp_array[num_back + i] = deq->deque[f];                                          	\
					f = (f + 1) % deq->max_items;;                                                      \
				}                                                                                       \
				for(size_t i=0; i<deq->num_items; i++) {                                                \
					deq->deque[i] = temp_array[i];                                                      \
				}                                                                                       \
				free(temp_array);                                                                       \
			                                                                                            \
				fi = (front.index + num_back) % deq->max_items;											\
				bi = (end.index + 1 + num_back) % deq->max_items;										\
				deq->front_ptr = deq->num_items;                                                        \
				deq->back_ptr = deq->max_items - 1;                                                     \
			}                                                                                           \
		}	                                                                                            \
                                                                                                        \
		Deque_##X##_quicksort(deq->deque, deq->compare, bi, fi);                                      	\
	}																									\
																										\
	void Deque_##X##_dtor(Deque_##X* deq) {																\
		free(deq->deque);																				\
	}																									\
																										\
	void Deque_##X##_ctor(Deque_##X* deq, bool (*f)(const X&, const X&)) {								\
		deq->num_items = 0;																				\
		strcpy(deq->type_name, "Deque_"#X);																\
		deq->compare = f;																				\
																										\
		deq->max_items = DEQUE_INIT_SIZE;																\
		deq->deque = (X*) malloc(DEQUE_INIT_SIZE * sizeof(X));											\
		deq->front_ptr = 0; 																			\
		deq->back_ptr = DEQUE_INIT_SIZE - 1;															\
																										\
		deq->dtor = Deque_##X##_dtor;																	\
		deq->size = Deque_##X##_size;																	\
		deq->empty = Deque_##X##_empty;																	\
		deq->push_back = Deque_##X##_push_back;															\
		deq->push_front = Deque_##X##_push_front;														\
		deq->front = Deque_##X##_front;																	\
		deq->back = Deque_##X##_back;																	\
		deq->pop_front = Deque_##X##_pop_front;															\
		deq->pop_back = Deque_##X##_pop_back;															\
		deq->clear = Deque_##X##_clear;																	\
		deq->sort = Deque_##X##_sort;																	\
																										\
		deq->begin = Deque_##X##_begin;																	\
		deq->end = Deque_##X##_end;																		\
		deq->at = Deque_##X##_at;																		\
																										\
		deq->double_max_items = Deque_##X##_double_max_items;											\
	}																									\
																										\
	bool Deque_##X##_equal(Deque_##X& deq1, Deque_##X& deq2) {											\
		if(deq1.num_items != deq2.num_items) return false;												\
		if(deq1.compare != deq2.compare) return false;													\
		if(deq1.num_items == 0) return true;															\
																										\
		int p1=deq1.front_ptr, p2=deq2.front_ptr;														\
		for(int i=0; i<(int)deq1.num_items; i++) {														\
			p1--;																						\
			if(p1 < 0) p1 = deq1.max_items - 1;															\
			p2--;																						\
			if(p2 < 0) p2 = deq2.max_items - 1;															\
																										\
			X x1 = deq1.deque[p1];																		\
			X x2 = deq2.deque[p2];                                                    					\
			if(deq1.compare(x1, x2)) return false;                                          			\
			if(deq1.compare(x2, x1)) return false;														\
		}                                                                                   			\
	                                                                                        			\
		return true;                                                                        			\
	}                                                                                       			\

#endif // DEQUE_H
