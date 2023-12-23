#ifndef EXCEPTIONSDSA
#define EXCEPTIONSDSA

#include <exception>
using std::exception;


class fileDoesNotExistException: exception {};
class fileCouldNotBeOpenedException: exception {};
class UnderflowException: exception { };
class IllegalArgumentException: exception { };
class ArrayIndexOutOfBoundsException: exception { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException: exception { };
class IteratorUninitializedException: exception { };





#endif