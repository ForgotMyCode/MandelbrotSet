#pragma once

#include <cstdlib>

#define check(CONDITION, EXIT_CODE) { \
	if(!( CONDITION )) [[unlikely]] { \
		exit( (EXIT_CODE) ); \
	} \
}

#define ERR_NULL_POINTER 100
#define ERR_BAD_DIMENSION 101
#define ERR_GLFW_INIT_FAILED 102
#define ERR_WINDOW_CREATION_FAILED 103
#define ERR_ALLOC_FAILED 104
#define ERR_BAD_STATE 105
#define ERR_SHAPE_MISMATCH 106