# Operating-Systems

Project for university assignment.

NOTE: The project requires a buffer size of 500, however, this makes it so the
programs take a lot to return any meaningful result, so in all solutions a
variable called `BUF_SIZE` can be adjusted to your liking. By default the value
is kept small (4 ~ 16) just so user feedback is quicker but all programs are
written so they can work with any non zero `BUF_SIZE`.

## Build (all)

Simply run `make`, you can set your compiler or include extra compiler flags by
editing the Makefile.

## Shared Memory Solution

Just run with (for 1000 iterations):
```
$ ./foodsec 1000
```

## Threaded Solution

Just run with (for 1000 iterations):
```
$ ./foodsec 1000
```

You can redirect the process `stderr` to `/dev/null` in case you want to only
see the display without debug logs Like so:

```
$ ./foodsec 1000 2>/dev/null
```

## FIFO Solution

This directory uses named pipes for IPC.
Example (run each command in separate terminals)

The `display` binary must be run first to establish the named pipes, the belt
processes may be run in any order.

```
$ ./display 1000
```
```
$ ./belt 1000 2 belt0.fifo
```
```
$ ./belt 2000 5 belt1.fifo
```


## Dependencies

- `phtread` support
- A C++17 compiler (`clang++` or `g++`)

