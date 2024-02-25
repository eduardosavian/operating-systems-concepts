#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_

#define _POSIX_C_SOURCE 200809L

#include "types.h"
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

static void microsleep(usize usec){
	usize rem = usec % 1000000;
	struct timespec t;
	t.tv_sec =  usec / 1000000,
	t.tv_nsec = rem * 1000,
	nanosleep(&t, NULL);
}

#endif /* include guard */
