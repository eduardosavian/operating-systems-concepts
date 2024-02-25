#include <cstdio>
#include <cstdlib>

#include <sys/mman.h>

#include "types.h"
#include "posix_utils.h"

namespace G {
constexpr usize BUF_SIZE = 32;
}

void show(f64 val){
	std::printf("[ %.2f ]\n", val);
}

struct Belt {
	usize delay; // Push delay, in ms
	f64 weight;
	f64* data;
	f64* acc;   // Shared accumulator
	usize cap;
	usize len;

	void add(f64 n){
		if((len + 1) >= cap){
			for(usize i = 0; i < n; i += 1){ *acc += data[i]; }

			for(usize i = 0; i < n; i += 1){ data[i] = 0; }
			len = 0;
		}
		data[len] = n;
		len += 1;
	}

	void run(){
		while(1){
			add(weight);
			std::fprintf(stderr,"belt: [%.1f | %zu] pushed.\n", weight, delay);

			microsleep(delay * 1000);
		}
	}

	Belt(uint delay, f64 weight, usize buf_size, f64* acc) :
		delay(delay), weight(weight), acc(acc), cap(buf_size), len(0) {
		data = new f64 [buf_size];
		for(usize i = 0; i < buf_size; i += 1){ data[i] = 0; }
	}

	~Belt(){
		delete[] data;
	}

};

int main(int argc, const char** argv){
	if(argc < 2){
		std::fprintf(stderr, "USAGE: foodsec [ITERATIONS]\n");
		std::abort();
	}
	usize iterations = atol(argv[1]);
	// Accumulators for belts
	f64* acc0 = (f64*)mmap(NULL, sizeof(*acc0),
												PROT_READ | PROT_WRITE,
												MAP_SHARED | MAP_ANON, -1, 0);
	f64* acc1 = (f64*)mmap(NULL, sizeof(*acc0),
												PROT_READ | PROT_WRITE,
												MAP_SHARED | MAP_ANON, -1, 0);
	pid_t pid_b0 = fork();

	if(pid_b0 == 0){
		pid_t pid_b1 = fork();
		if(pid_b1 == 0){
			Belt b0(100, 2.0, G::BUF_SIZE / 2, acc0);
			b0.run();
		} else {
			Belt b1(200, 5.0, G::BUF_SIZE / 2, acc1);
			b1.run();
		}
	} else {
		for(usize i = 0; i < iterations; i += 1){
			show(*acc0 + *acc1);
			microsleep(2000000);
		}
		return 0;
	}

	return 0;
}

