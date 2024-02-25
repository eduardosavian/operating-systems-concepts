// Representation of a task in the system.

#ifndef _task_h_include_
#define _task_h_include_

typedef struct Task Task;

struct Task {
	char *name;
	int tid;
	int priority;
	int burst;
};

extern Task task_new(char* name, int id, int priority, int burst);
extern void task_del(Task* t);

#endif /* Include guard */
