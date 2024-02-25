#ifndef _strdup_h_include_
#define _strdup_h_include_

#include <string.h>
#include <stdlib.h>

static char* str_clone(const char* s){
	int n = strlen(s);
	char* dup = malloc(n + 1);
	memcpy(dup, s, n);
	dup[n] = 0;
	return dup;
}

static char* str_slice(const char* s, int begin, int end){
	if(begin >= end){ return NULL; }
	int size = end - begin;
	char* sl = calloc(size + 1, 1);
	for(int i = 0; i < size; i += 1){
		sl[i] = s[begin + i];
	}
	sl[size] = 0;
	return sl;
}

#endif /* Include guard */
