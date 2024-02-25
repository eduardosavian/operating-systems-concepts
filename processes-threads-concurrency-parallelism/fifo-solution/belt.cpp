#include <array>
#include <ctime>
#include <cstdio>
#include <cstdlib>

#include <fcntl.h>
#include <unistd.h>

#include "types.h"
#include "posix_utils.h"

void serialize_f64(byte* buf, f64 n){
	byte* p = reinterpret_cast<byte*>(&n);
	for(usize i = 0; i < sizeof(n); i += 1){
		buf[i] = p[i];
	}
}

struct Belt {
	usize delay; // Push delay, in ms
	f64   weight;
	const char* fifo_path;

	void run(){
		byte buf[sizeof(f64) + 1] = {0};
		serialize_f64(buf, weight);
		while(1){
			int fd = open(fifo_path, O_WRONLY);
			if(fd < 0){
				std::fprintf(stderr, "Failed to open file: %s\n", fifo_path);
				return;
			}
			write(fd, buf, sizeof(f64));
			printf("%.2f\n", weight);
			close(fd);

			microsleep(delay * 1000);
		}
	}

	Belt(){}
	Belt(uint d, f64 w, const char* p) : delay(d), weight(w), fifo_path(p) {}
};

int main(int argc, const char** argv){
	if(argc < 4){
		std::fprintf(stderr, "Usage: belt [DELAY] [VAL] [FIFO]\n");
		return 1;
	}
	uint delay = atoi(argv[1]);
	f64 weight = atof(argv[2]);
	const char* file = argv[3];

	Belt b(delay, weight, file);
	b.run();
	return 0;
}

