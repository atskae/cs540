#ifndef DEQUE_MYCLASS_H
#define DEQUE_MYCLASS_H

// Non-macro version

#define DEQUE_INIT_SIZE 4

// forward declaration;
struct Deque_MyClass;

struct MyClass {
	int id;
	char name[25];

    bool operator==(MyClass& m) {
    	if(id == m.id && strcmp(name, m.name) == 0) return true;
		else return false; 
    }
};

void MyClass_print(const MyClass *o);
bool MyClass_less_by_id(const MyClass &o1, const MyClass &o2);
bool MyClass_less_by_name(const MyClass &o1, const MyClass &o2);

struct Deque_MyClass_Iterator {
	Deque_MyClass* deq; // pointer to container
	// maintain circular traversal of the deque as dynamic array
	int index; // array index into deque
	// to distinguish if front_ptr == back_ptr (full or empty) ; 0 = at the last element ; -1 where end iterator is
	int num_to_end; // to deq.end()

	// methods
	void (*inc)(Deque_MyClass_Iterator*); // goes toward the end of deque
	void (*dec)(Deque_MyClass_Iterator*); // goes toward the front of deque
	MyClass& (*deref)(Deque_MyClass_Iterator*);
};

bool Deque_MyClass_Iterator_equal(Deque_MyClass_Iterator it1, Deque_MyClass_Iterator it2);

struct Deque_MyClass {
	size_t num_items;
	char type_name[sizeof "Deque_MyClass"];

	MyClass* deque; // actual deque contents
	int front_ptr;
	int back_ptr;
	size_t max_items; // when full, the deque size is doubled

	bool (*compare)(const MyClass&, const MyClass&);

	// "methods"
	size_t (*size)(Deque_MyClass*);
	bool (*empty)(Deque_MyClass*);
	void (*push_back)(Deque_MyClass*, const MyClass);
	void (*push_front)(Deque_MyClass*, const MyClass);
	MyClass& (*front)(Deque_MyClass*);
	MyClass& (*back)(Deque_MyClass*);
	void (*dtor)(Deque_MyClass*);

	void (*pop_front)(Deque_MyClass*);
	void (*pop_back)(Deque_MyClass*);

	Deque_MyClass_Iterator (*begin)(Deque_MyClass*);
	Deque_MyClass_Iterator (*end)(Deque_MyClass*);

	MyClass& (*at)(Deque_MyClass* deq, int from_front);	
	void (*clear)(Deque_MyClass* deq);

	void (*sort)(Deque_MyClass* deq, Deque_MyClass_Iterator front, Deque_MyClass_Iterator end);

	// helper "methods"
	void (*double_max_items)(Deque_MyClass*);
	void (*print)(Deque_MyClass*);
};

bool compare(const MyClass& x, const MyClass& y);
void Deque_MyClass_ctor(Deque_MyClass* deq, bool (*f)(const MyClass& x, const MyClass& y));
bool Deque_MyClass_equal(Deque_MyClass& deq1, Deque_MyClass& deq2);
void Deque_MyClass_dtor(Deque_MyClass* deq);

#endif // DEQUE_MYCLASS_H
