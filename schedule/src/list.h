#ifndef _queue_h_include_
#define _queue_h_include_

#include "task.h"

typedef struct ListNode ListNode;
typedef struct List List;

struct ListNode {
	ListNode* next;
	Task *task;
};

struct List {
	ListNode* head;
	int len;
};

// Create list
extern List list_new();
// De-alloc list
extern void list_del(List* l);
// Add element to list
extern void list_add(List* l, Task* task);
// Search and remove element from list
extern void list_rm(List* l, Task* task);
// Get task at index
extern ListNode* list_at(List* l, int idx);
// Print list
extern void list_display(const List* l);

#endif /* Include guard */
