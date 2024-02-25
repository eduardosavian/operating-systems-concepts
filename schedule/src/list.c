#include "list.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

List list_new(){
	return (List) {
		.head = NULL,
		.len = 0,
	};
}

static void list_node_dealloc(ListNode* node){
	if(node == NULL){ return; }
	task_del(node->task);
	free(node->task);
	free(node);
}

ListNode* list_at(List* l, int idx){
	if(l == NULL) { return NULL; }
	if(idx >= l->len){ return NULL; }
	int i = 0;
	ListNode* cur = l->head;
	while(i <= idx){
		cur = cur->next;
		i += 1;
	}
	return cur;
}


void list_del(List* l){
	if(l == NULL){ return; }
	ListNode* cur = l->head;
	while(cur != NULL){
		ListNode* next = cur->next;
		list_node_dealloc(cur);
		cur = next;
	}
	free(cur);
}

void list_add(List* l, Task* task){
	ListNode* new_node = malloc(sizeof(*new_node));
	new_node->task = task;

	new_node->next = l->head;
	l->head = new_node;
	l->len += 1;
}

void list_rm(List* l, Task* task){
	if(l == NULL){ return; }
	ListNode* cur = l->head;
	ListNode* prev = NULL;
	while(cur != NULL){
		// TODO: Change this to pointer instead of ID comparison
		if(cur->task->tid == task->tid){
			if(prev == NULL){
				l->head = cur->next;
			} else {
				prev->next = cur->next;
			}
			list_node_dealloc(cur);
			l->len -= 1;
			return;
		}
		prev = cur;
		cur = cur->next;
	}
}

static void display_task(const Task* t){
	printf("id:%d, burst:%d, priority:%d, name:%s\n", t->tid, t->burst, t->priority, t->name);
}

void list_display(const List* l){
	if(l == NULL){ return; }
	ListNode* cur = l->head;
	if(l->head == NULL){ return; }

	int i = 0;
	while(cur->next != NULL){
		printf("[%d] ", i);
		display_task(cur->task);
		i += 1;
		cur = cur->next;
	}
	printf("[%d] ", i);
	display_task(cur->task);

}
