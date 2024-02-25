#include <array>
#include <ctime>
#include <cstdio>
#include <cstdlib>

#include "types.h"
#include "posix_utils.h"

struct Display {
	f64 val;

	void show(){
		std::printf("[ %.2f ]\n", val);
	}

	void run(usize iter){
		for(usize i = 0; i < iter; i += 1){
			show();
			microsleep(2 * 1000000);
		}
	}
};

namespace G { // Global var namespace
Display display;
constexpr usize BUF_SIZE = 32;
std::array<f64, BUF_SIZE> weigh_in_buffer = {0};
usize buf_index = 0;
pthread_mutex_t buf_lock = PTHREAD_MUTEX_INITIALIZER;
usize iterations = 0;
}

void push_weight(f64 w){
	pthread_mutex_lock(&G::buf_lock);
	if(G::buf_index >= G::BUF_SIZE){ // Clear buffer and update display
		f64 acc = 0;
		// TODO: Vectorize with OpenMP
		for(const auto& n : G::weigh_in_buffer){ acc += n; }
		G::display.val += acc;

		G::buf_index = 0;
		// TODO: Vectorize with OpenMP
		for(auto& n : G::weigh_in_buffer){ n = 0; }
	}
	
	G::weigh_in_buffer[G::buf_index] = w;
	G::buf_index += 1;
	pthread_mutex_unlock(&G::buf_lock);
}

struct Belt {
	usize delay; // Push delay, in ms
	f64 weight;

	void run(){
		while(1){
			std::fprintf(stderr,"belt: [%.1f | %zu] pushed.\n", weight, delay);
			push_weight(weight);
			microsleep(delay * 1000);
		}
	}

	Belt(){}
	Belt(uint d, f64 w) : delay(d), weight(w) {}
};

void* belt_run_wrapper(void* belt){
	Belt* b = (Belt*)belt;
	pthread_detach(pthread_self());
	b->run();
	return NULL;
}

void* display_run_wrapper(void* display){
	Display* d = (Display*)display;
	d->run(G::iterations);
	return NULL;
}

int main(int argc, const char** argv){
	if(argc < 2){
		std::fprintf(stderr, "USAGE: foodsec [ITERATIONS]\n");
		std::abort();
	}
	G::iterations = atoi(argv[1]);
	Belt* belt0 = new Belt(200, 5.0);
	Belt* belt1 = new Belt(100, 2.0);
	pthread_t belt0_thread, belt1_thread, display_thread;

	if(pthread_create(&display_thread, NULL, display_run_wrapper, &G::display) != 0){
		std::fprintf(stderr, "Failed to create worker thread.\n");
		std::abort();
	}
	if(pthread_create(&belt0_thread, NULL, belt_run_wrapper, belt0) != 0){
		std::fprintf(stderr, "Failed to create worker thread.\n");
		std::abort();
	}
	if(pthread_create(&belt1_thread, NULL, belt_run_wrapper, belt1) != 0){
		std::fprintf(stderr, "Failed to create worker thread.\n");
		std::abort();
	}

	// pthread_join(belt0_thread, NULL);
	// pthread_join(belt1_thread, NULL);
	pthread_join(display_thread, NULL);

	delete belt0;
	delete belt1;
	return 0;
}

