// Round Robin scheduler implementation
#include <stdio.h>
#include <stdlib.h>
#include "schedule.h"

struct Scheduler{
	List tasks;
	int last_id;
};

Scheduler* sched_new(){
	Scheduler* sc = (Scheduler*)malloc(sizeof(Scheduler));
	sc->tasks = list_new();
	sc->last_id = 0;

	return sc;
}

void sched_consume_list(Scheduler* sc, List* l){
	list_del(&sc->tasks);
	sc->tasks = *l;
	*l = (List){.len = 0, .head = NULL};
}

void sched_remove(Scheduler* sc, Task* task){
	list_rm(&sc->tasks, task);
}

void sched_run(Scheduler* sc) {
	if (sc == NULL) {
		printf("Scheduler not initialized.\n");
		return;
	}

	if (sc->tasks.len == 0) {
		printf("No tasks in the scheduler.\n");
		return;
	}

	ListNode* cur = sc->tasks.head;
	while (cur != NULL) {
		Task* task = cur->task;

		if (task->burst > 0) {
			if (task->burst > QUANTUM) {
				run(task, QUANTUM);
				task->burst -= QUANTUM;
			}
			else {
				run(task, task->burst);
				task->burst = 0;
				printf("Task [%s] [%d] finished.\n", task->name, task->tid);
				ListNode* next = cur->next;
				list_rm(&sc->tasks, task);
				cur = next;
				continue;
			}
		}

		cur = cur->next;

		if (cur == NULL) {
			cur = sc->tasks.head;
		}

		if(sc->tasks.len == 0){
			printf("All tasks finished.\n");
			break;
		}
	}
}

void sched_add(Scheduler* sc, char *name, int priority, int burst){
	Task* new_task = malloc(sizeof(*new_task));
	sc->last_id += 1;
	*new_task = task_new(name, sc->last_id, priority, burst);

	list_add(&sc->tasks, new_task);
}

void sched_del(Scheduler* sc){
	list_del(&sc->tasks);
	free(sc);
}
