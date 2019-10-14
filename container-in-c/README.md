# Containers in C

## How to Run
To compile, run `make`. To run the provided `test.cpp`, run `./test-run.exe`.

## Directories
* `res`: Resources, such as project description, test cases, and examples.
* `deque_myclass`: A non-macro version of a deque, which only holds `MyClass` structs. Used for debugging and checking for memory errors before implementing as a macro.

## Questions
* Given this syntax, `_##X##_ctor()`, why is `X&` ok? (but not `X##&`)?
* ~~`sizeof(deq.type_name)` will always return 8 bytes (size of a pointer) if `type_name` is a `char*`. So `type_name` must be a static array(?). How to get the length of the `type_name` at preprocessor time?~~
* Why are some methods taking references (`Deque_X_equal`) while most take pointers?
