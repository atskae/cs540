#ifndef DEQUE_H
#define DEQUE_H

#define Deque_DEFINE(X)					\
	struct Deque_##X {					\
		int size;						\
		char* type_name;				\
	};									\

#endif // DEQUE_H
