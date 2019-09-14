#ifndef DEQUE_MYCLASS_H
#define DEQUE_MYCLASS_H

// Non-macro version

struct MyClass {
	int id;
	char* name[10];
};

struct Deque_MyClass {
	size_t num_items;
	char* type_name;

	bool (*compare)(const MyClass&, const MyClass&);

	// "methods"
	size_t (*size)(Deque_MyClass*);
	bool (*empty)(Deque_MyClass*);
};

bool compare(const MyClass& x, const MyClass& y);
void Deque_MyClass_ctor(Deque_MyClass& deq, bool (*f)(const MyClass& x, const MyClass& y));

#endif // DEQUE_MYCLASS_H
