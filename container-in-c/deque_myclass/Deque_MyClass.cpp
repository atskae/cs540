#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <typeinfo>

#include "Deque_MyClass.hpp"

void MyClass_print(const MyClass *o) {
    printf("%d\n", o->id);
    printf("%s\n", o->name);
}

bool MyClass_less_by_id(const MyClass &o1, const MyClass &o2) {
    return o1.id < o2.id;
}

bool MyClass_less_by_name(const MyClass &o1, const MyClass &o2) {
    return strcmp(o1.name, o2.name) < 0;
}

// Iterator

MyClass& Deque_MyClass_Iterator_deref(Deque_MyClass_Iterator* it) {
	// this would work even if it = end()...
	return it->deq->deque[it->index];
}

// increment means, go toward the end of the deque
void Deque_MyClass_Iterator_inc(Deque_MyClass_Iterator* it) {
	if(it->num_to_end == 0) return;

	it->index--;
	if(it->index < 0) it->index = it->deq->max_items - 1;
	it->num_to_end--;
}

// decrement means, go toward the front of the deque
void Deque_MyClass_Iterator_dec(Deque_MyClass_Iterator* it) {
	it->index++;
	assert(it->index >= 0);
	if((size_t)it->index >= it->deq->max_items) it->index = 0;
	it->num_to_end++;
}


Deque_MyClass_Iterator Deque_MyClass_end(Deque_MyClass* deq) {
	Deque_MyClass_Iterator it;
	it.deq = deq;
	it.index = deq->back_ptr;
	it.num_to_end = 0; // at the end past the last element
	// methods
	it.inc = Deque_MyClass_Iterator_inc;
	it.dec = Deque_MyClass_Iterator_dec;
	it.deref = Deque_MyClass_Iterator_deref;
	return it; // haha, "return it"
}

// returns a reference to the front
Deque_MyClass_Iterator Deque_MyClass_begin(Deque_MyClass* deq) {
	if(deq->num_items == 0) return deq->end(deq);
	Deque_MyClass_Iterator it;
	it.deq = deq;
	if(deq->front_ptr == 0) it.index = deq->max_items - 1;
	else it.index = deq->front_ptr - 1;
	it.num_to_end = deq->num_items; 
	// methods
	it.inc = Deque_MyClass_Iterator_inc;
	it.dec = Deque_MyClass_Iterator_dec;
	it.deref = Deque_MyClass_Iterator_deref;

	return it;
}

bool Deque_MyClass_Iterator_equal(Deque_MyClass_Iterator it1, Deque_MyClass_Iterator it2) {
	return (it1.index == it2.index) && (it1.num_to_end == it2.num_to_end);
}

// Deque "methods"

size_t Deque_MyClass_size(Deque_MyClass* deq) {
	return deq->num_items;
}

bool Deque_MyClass_empty(Deque_MyClass* deq) {
	return deq->num_items == 0;
}

MyClass& Deque_MyClass_at(Deque_MyClass* deq, int from_front) {

	assert(from_front >= 0);
	assert((size_t)from_front < deq->num_items);
	int idx = deq->front_ptr; // points to next empty slot ; move pointer to move to front element
	idx--;
	if(idx < 0) idx = deq->max_items - 1;

	if(idx - from_front < 0) idx = (deq->max_items - (from_front - idx));
	else idx = idx - from_front;
	//for(int i=0; i<from_front; i++) {
	//	idx--;
	//	if(idx < 0) idx = deq->max_items - 1;
	//}
	
	return deq->deque[idx];
}

void Deque_MyClass_clear(Deque_MyClass* deq) {
	if(deq->num_items == 0) return;
	
	deq->num_items = 0;
	deq->front_ptr = 1;
	deq->back_ptr = deq->max_items - 1;		

	// should I shrink capacity here to DEQUE_INIT_SIZE?
}

void Deque_MyClass_print(Deque_MyClass* deq) {
	printf("\n%lu/%lu items, front_ptr=%i, back_ptr=%i\n",
		deq->num_items, deq->max_items, deq->front_ptr, deq->back_ptr);

	if(deq->empty(deq)) {
		printf("Deque is empty.\n");
		return;
	}
	int ptr = deq->front_ptr - 1; // -1 since front_ptr points to the next free element
	if(ptr < 0) ptr = deq->max_items - 1;

	printf("===FRONT===\n");
	for(int i=0; i<(int)deq->num_items; i++) {
		MyClass* m = &deq->deque[ptr];
		printf("idx=%i: %s,%i\n", ptr, m->name, m->id);
		ptr--;
		if(ptr < 0) ptr = deq->max_items - 1;
	}
	printf("===BACK===\n");
}

void Deque_MyClass_double_max_items(Deque_MyClass* deq) {
	assert(deq->num_items == deq->max_items);

	// double the capacity
	size_t deq_old_size = deq->max_items;
	deq->max_items *= 2;
	deq->deque = (MyClass*) realloc(deq->deque, deq->max_items * sizeof(MyClass));

	// move the objects that are in the "back"
	//        b
	// [x x x x x x x _ _ _ _]
	// to
	// [x x x x _ _ _ _ x x x]
	int new_back_ptr = deq->max_items - 1;
	int lower_bound = deq->back_ptr;
	assert(lower_bound >=0);
	if((size_t)lower_bound == deq_old_size-1) lower_bound = -1;
	for(int i=deq_old_size-1; i>lower_bound; i--) {
		deq->deque[new_back_ptr] = deq->deque[i];
		new_back_ptr--;
	}
	deq->back_ptr = new_back_ptr;
}

/* Methods */

void Deque_MyClass_push_back(Deque_MyClass* deq, const MyClass m) {
	//printf("push_back %s,%i\n", m.name, m.id);
	if(deq->num_items == deq->max_items) {
		deq->double_max_items(deq);
	}

	deq->deque[deq->back_ptr] = m;
	deq->back_ptr--;
	if(deq->back_ptr < 0) deq->back_ptr = deq->max_items - 1;
	deq->num_items++;
}

void Deque_MyClass_push_front(Deque_MyClass* deq, const MyClass m) {
	//printf("push_front %s,%i\n", m.name, m.id);
	if(deq->num_items == deq->max_items) {
		deq->double_max_items(deq);
	}

	deq->deque[deq->front_ptr] = m;
	deq->front_ptr++;
	assert(deq->front_ptr >= 0);
	if((size_t)deq->front_ptr == deq->max_items) deq->front_ptr = 0;
	deq->num_items++;
}

MyClass& Deque_MyClass_front(Deque_MyClass* deq) {
	int ptr = deq->front_ptr - 1;
	if(ptr < 0) ptr = deq->max_items - 1;

	return deq->deque[ptr];
}

MyClass& Deque_MyClass_back(Deque_MyClass* deq) {
	int ptr = deq->back_ptr + 1;
	//if(ptr < 0) ptr = 0;
	if((size_t)ptr == deq->max_items) ptr = 0;

	return deq->deque[ptr];
}

void Deque_MyClass_pop_front(Deque_MyClass* deq) {
	if(deq->num_items == 0) {
	//	printf("pop_front failed: deque is empty.\n");
		return;
	}

	//MyClass f = deq->front(deq);
	//printf("pop_front %s,%i\n", f.name, f.id);
	
	deq->front_ptr--;
	deq->num_items--;
	if(deq->front_ptr < 0) deq->front_ptr = deq->max_items - 1;
	
	if(deq->empty(deq)) {
		deq->front_ptr = 0;
		deq->back_ptr = deq->max_items - 1;
	}
}

void Deque_MyClass_pop_back(Deque_MyClass* deq) {
	if(deq->num_items == 0) {
		printf("pop_back failed: deque is empty.\n");
		return;
	}

	//MyClass f = deq->back(deq);
	//printf("pop_back %s,%i\n", f.name, f.id);

	deq->back_ptr++;
	deq->num_items--;
	assert(deq->back_ptr >= 0);
	if((size_t)deq->back_ptr == deq->max_items) deq->back_ptr = 0;
	
	if(deq->empty(deq)) {
		deq->front_ptr = 0;
		deq->back_ptr = deq->max_items - 1;
	}
}

bool Deque_MyClass_equal(Deque_MyClass& deq1, Deque_MyClass& deq2) {
	if(deq1.num_items != deq2.num_items) return false;	
	if(deq1.compare != deq2.compare) return false;
	if(deq1.num_items == 0) return true; // both are empty

	// both deque have the same number of items
	int p1=deq1.front_ptr, p2=deq2.front_ptr;
	for(int i=0; i<(int)deq1.num_items; i++) {
		p1--;
		if(p1 < 0) p1 = deq1.max_items - 1;
		p2--;
		if(p2 < 0) p2 = deq2.max_items - 1;
		
		MyClass x1 = deq1.deque[p1];
		MyClass x2 = deq2.deque[p2];
		//if(x1 == x2) continue;
		if(deq1.compare(x1, x2)) {
			return false;
		}
		if(deq1.compare(x2, x1)) {
			return false;
		}
	}

	return true;
}

void Deque_MyClass_swap(MyClass* array, int i, int j) {
	MyClass temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

// https://www.geeksforgeeks.org/quick-sort/
int Deque_MyClass_partition(MyClass* array, bool (*compare)(const MyClass&, const MyClass&), int b, int f) { // back and front index
	MyClass pivot = array[f];
	int i = b-1;
	for(int j=b; j<=f-1; j++) {
		if(!compare(array[j], pivot)) { // descending order, because the front is rightmost
			i++;
			// swap
			Deque_MyClass_swap(array, i, j);
		}
	}
	// swap
	Deque_MyClass_swap(array, i+1, f);

	return i+1;
}

// https://www.geeksforgeeks.org/quick-sort/
void Deque_MyClass_quicksort(MyClass* array, bool (*compare)(const MyClass&, const MyClass&), int b, int f) { // back and front index
	if(b < f) {
		int pi = Deque_MyClass_partition(array, compare, b, f);
		Deque_MyClass_quicksort(array, compare, b, pi-1);
		Deque_MyClass_quicksort(array, compare, pi+1, f);
	}
}

void Deque_MyClass_sort(Deque_MyClass* deq, Deque_MyClass_Iterator front, Deque_MyClass_Iterator end) { // end = exclusive (since end is one past the last element)
	if(deq->num_items <= 1) return;
	
	//printf("sort() was called.\n");
	//
	//printf("Before shifting:\n");
	//deq->print(deq);
	//printf("Before shifting end\n");

	int bi = (end.index + 1) % deq->max_items; // end is one past the last element ; go back one element
	int fi = front.index;

	printf("end.index=%i, front.index=%i\n", end.index, front.index);	
	printf("front_ptr=%i, back_ptr=%i, max_items=%lu\n", deq->front_ptr, deq->back_ptr, deq->max_items);
	if(deq->front_ptr <= deq->back_ptr) {
		assert(deq->back_ptr >= 0); 
		if(deq->num_items != deq->max_items && (size_t) deq->back_ptr != deq->max_items - 1) { // split at wrap around
			MyClass* temp_array = (MyClass*) malloc(deq->num_items * sizeof(MyClass));
			// copy everything behind back_ptr
			int num_back = deq->max_items - deq->back_ptr - 1;
			bi = (deq->back_ptr + 1) % deq->max_items;
			printf("Split at wrap around. bi=%i, fi=%i, num_back=%i\n", bi, fi, num_back);
			for(int i=0; i<num_back; i++) {
				temp_array[i] = deq->deque[bi];
				bi = (bi + 1) % deq->max_items;
			}
			// copy everthing behind front_ptr
			fi = 0;
			for(int i=0; i<deq->front_ptr; i++) {
				temp_array[num_back + i] = deq->deque[fi];
				fi = (fi + 1) % deq->max_items;
			}
			
			// copy temp to deque
			for(size_t i=0; i<deq->num_items; i++) {
				deq->deque[i] = temp_array[i];
			}
			//printf("Temp array\n");
			//for(size_t i=0; i<deq->num_items; i++) {
			//	printf("idx=%lu, %s,%i\n", i, temp_array[i].name, temp_array[i].id);
			//}
			free(temp_array);
			printf("Temp array end\n");	
	
			// update pointers	
			fi = (front.index + num_back) % deq->max_items;
			bi = (end.index + 1 + num_back) % deq->max_items; // end.index + 1 since end.index points to one past the last element
			deq->front_ptr = deq->num_items;
			deq->back_ptr = deq->max_items - 1;
		
		} 
	}	

	//printf("After shifting\n");
	//deq->print(deq);
	//printf("After shifting end\n");
	
	//// shift all elements from index 0 to max_items - 1
	//if(deq->front_ptr <= deq->back_ptr) {
	//	// get number of items behind the back_ptr = # times we shift
	//	int num_back = deq->max_items - deq->back_ptr - 1;
	//	for(int i=0; i<num_back; i++) {
	//		MyClass temp = deq->deque[deq->max_items - 1];
	//		// shift everything toward the right
	//		for(int j=deq->max_items-2; j>=0; j--) {
	//			deq->deque[j+1] = deq->deque[j];	
	//		}
	//		deq->deque[0] = temp;
	//	}

	//	// update the deque's front and back ptrs
	//	deq->front_ptr = deq->num_items;
	//	if((size_t)deq->front_ptr == deq->max_items) deq->front_ptr = 0;
	//	deq->back_ptr = deq->max_items - 1;

	//	// update the iterators
	//	front.index = (front.index + num_back) % deq->max_items;
	//	end.index = (end.index + num_back) % deq->max_items;
	//}

	//printf("After shifting:\n");
	//deq->print(deq);
	// when sorting, we need to get one before the end iterator 
	//int back = end.index + 1;
	//assert(back >= 0);
	//if((size_t)back == deq->max_items) back = 0;
	
	// sort!
	//printf("about to sort: bi=%i, fi=%i\n", bi, fi);
	//fflush(stdout);
	//Deque_MyClass_quicksort(deq->deque, deq->compare, back, front.index);
	Deque_MyClass_quicksort(deq->deque, deq->compare, bi, fi);
}

void Deque_MyClass_ctor(Deque_MyClass* deq, bool (*f)(const MyClass&, const MyClass&)) {
	deq->num_items = 0;
	strcpy(deq->type_name, "Deque_MyClass");
	deq->compare = f;

	// f             b
	// 0 0 0 0 0 0 0 0
	deq->max_items = DEQUE_INIT_SIZE;
	deq->deque = (MyClass*) malloc(DEQUE_INIT_SIZE * sizeof(MyClass));
	deq->front_ptr = 0; // front_ptr increments
	deq->back_ptr = DEQUE_INIT_SIZE - 1; // back_ptr decrements
	
	// "methods"
	deq->size = Deque_MyClass_size;
	deq->empty = Deque_MyClass_empty;
	deq->push_back = Deque_MyClass_push_back;
	deq->push_front = Deque_MyClass_push_front;
	deq->front = Deque_MyClass_front;
	deq->back = Deque_MyClass_back;
	deq->dtor = Deque_MyClass_dtor;

	deq->pop_front = Deque_MyClass_pop_front;
	deq->pop_back = Deque_MyClass_pop_back;

	deq->begin = Deque_MyClass_begin;
	deq->end = Deque_MyClass_end;

	deq->at = Deque_MyClass_at;	
	deq->clear = Deque_MyClass_clear;
	deq->sort = Deque_MyClass_sort;

	// helper "methods"
	deq->double_max_items = Deque_MyClass_double_max_items;
	deq->print = Deque_MyClass_print;
}

void Deque_MyClass_dtor(Deque_MyClass* deq) {
	printf("%s destructor()\n", deq->type_name);
	free(deq->deque);
}
