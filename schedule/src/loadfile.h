#ifndef _load_h_include_
#define _load_h_include_

#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include "str_utils.h"
#include "list.h"

static char* load_file(const char* path, int* bytes_read){
	FILE* f = fopen(path, "r");
	char* data = NULL;
	int start, end, size;
	fseek(f, 0, SEEK_END);
	end = ftell(f);
	rewind(f);
	start = ftell(f);
	size = end - start;
	data = malloc(size + 1);
	*bytes_read = fread(data, 1, size, f);
	fclose(f);
	data[size] = 0;
	return data;
}

static Task* parse_task(const char* s, int tid, int n){
	char* name   = NULL;
	int priority = 0;
	int burst    = 0;

	int begin = 0;
	int end = 0;
	int i = 0;

	{ // Task name
		while((s[i] != ',') && (i < n)){
			i += 1;
		}
		end = i; 
		name = str_slice(s, begin, end);
		i += 1;
		begin = i;
	}

	{ // Task priority
		while((s[i] != ',') && (i < n)){
			i += 1;
		}
		end = i; 
		char* tmp = str_slice(s, begin, end);
		priority = atoi(tmp);
		free(tmp);
		i += 1;
		begin = i;
	}

	{ // Task burst
		while((s[i] != ',') && (i < n)){
			i += 1;
		}
		end = i; 
		char* tmp = str_slice(s, begin, end);
		burst = atoi(tmp);
		free(tmp);
		begin = i + 1;
	}

	Task* t = malloc(sizeof(*t));
	*t = (Task){
		.tid = tid,
		.burst = burst,
		.priority = priority,
		.name = name,
	};

	return t;
}

static int line_count(const char* s, int n){
	int nl = 1;
	for(int i = 0; i < n; i += 1){
		if(s[i] == '\n'){ nl += 1; }
	}
	return nl;
}

static char** split_lines(const char* s, int n, int* lines_read){
	int lc = line_count(s, n);
	char** lines = calloc(lc + 1, sizeof(*lines));
	int begin = 0;
	int end = 0;
	int l_idx = 0;

	for(int i = 0; i < n; i += 1){
		if(s[i] == '\n'){
			end = i;
			lines[l_idx] = str_slice(s, begin, end);
			begin = end + 1;
			l_idx += 1;
		}
	}

	if(lines_read){ *lines_read = lc; }

	return lines;
}

static List parse_tasks(const char* s, int n){
	List l = list_new();
	int line_count;
	char** lines = split_lines(s, n, &line_count);
	int id = 0;

	for(int i = 0; i < line_count; i += 1){
		if(lines[i]){
			int line_len = strlen(lines[i]);
			Task* t = parse_task(lines[i], id, line_len);
			list_add(&l, t);
			// printf("%d len:%zu : %s\n", i, strlen(lines[i]), lines[i]);
			id += 1;
			free(lines[i]);
			lines[i] = NULL;
		}
	}

	free(lines);
	return l;
}

#endif /* Include guard */
