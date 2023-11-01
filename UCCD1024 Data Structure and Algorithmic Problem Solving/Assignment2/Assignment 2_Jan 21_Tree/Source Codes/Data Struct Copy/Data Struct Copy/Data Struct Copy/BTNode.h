#ifndef BTNode_type
#define BTNode_type

#include "Student.h"

using type = Student;

struct BTNode {

		type	item;
		BTNode	*left, *right;
		BTNode(type);

		// New add
		int height;	// height level
};


#endif