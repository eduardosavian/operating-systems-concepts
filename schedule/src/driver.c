/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "loadfile.h"
#include "schedule.h"

static void display_task(const Task* t){
	printf("id:%d, burst:%d, priority:%d, name:%s\n", t->tid, t->burst, t->priority, t->name);
}

int main(int argc, char *argv[]){
	if(argc < 2){
		fprintf(stderr, "usage: %s [FILE]\n", argv[0]);
		return EXIT_FAILURE;
	}
	char* filedata = NULL;
	int filebytes = 0;
	Scheduler* sc = sched_new();

	filedata = load_file(argv[1], &filebytes);
	// printf("--- TASK FILE ---\n%s\n--- EOF ---\n", filedata);

	List tasks = parse_tasks(filedata, filebytes);
	sched_consume_list(sc, &tasks);

	// sched_add(sc, "Task 1", 1, 50);
	// sched_add(sc, "Task 2", 5, 50);
	// sched_add(sc, "Task 3", 6, 50);
	// sched_add(sc, "Task 4", 5, 50);
	// sched_add(sc, "Task 5", 4, 50);
	// sched_add(sc, "Task 6", 4, 50);

	// invoke the scheduler
	sched_run(sc);

	// Cleanup
	free(filedata);
	sched_del(sc);
	return 0;
}
