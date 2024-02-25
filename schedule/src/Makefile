CC := gcc
override CFLAGS := -O2 -pipe -march=native -Wall -Wextra -fPIC -I. -Wno-unused-function $(CFLAGS)
override LDFLAGS := $(LDFLAGS) -lc -lm -L.

.PHONY: all clean list

all: rr priority_rr fcfs

list:
	@echo "Build targets:"
	@echo "  all, rr, fcfs, priority_rr"
	@echo "Build options:"
	@echo "  CC = $(CC)"
	@echo "  CFLAGS = $(CFLAGS)"
	@echo "  LDFLAGS = $(LDFLAGS)"

rr: driver.o list.o CPU.o schedule_rr.o loadfile.h task.o
	$(CC) $(CFLAGS) -o rr driver.o task.o schedule_rr.o list.o CPU.o $(LDFLAGS)

priority_rr: driver.o list.o CPU.o schedule_rr_p.o loadfile.h task.o
	$(CC) $(CFLAGS) -o priority_rr task.o driver.o schedule_rr_p.o list.o CPU.o $(LDFLAGS)

fcfs: driver.o list.o CPU.o schedule_fcfs.o loadfile.h task.o
	$(CC) $(CFLAGS) -o fcfs task.o driver.o schedule_fcfs.o list.o CPU.o $(LDFLAGS)

driver.o: driver.c schedule.h
	$(CC) $(CFLAGS) -c driver.c

schedule_rr.o: schedule_rr.c schedule.h
	$(CC) $(CFLAGS) -c schedule_rr.c

schedule_rr_p.o: schedule_rr_p.c schedule.h
	$(CC) $(CFLAGS) -c schedule_rr_p.c

schedule_fcfs.o: schedule_fcfs.c schedule.h
	$(CC) $(CFLAGS) -c schedule_fcfs.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

task.o: task.c task.h
	$(CC) $(CFLAGS) -c task.c

CPU.o: CPU.c CPU.h
	$(CC) $(CFLAGS) -c CPU.c

clean:
	rm -rf *.o
	rm -rf rr
	rm -rf priority_rr
	rm -rf fcfs
