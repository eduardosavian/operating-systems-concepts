#include <array>
#include <ctime>
#include <cstdio>
#include <cstdlib>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include "types.h"
#include "posix_utils.h"

f64 read_f64(int fd){
	f64 n;
	byte* p = (byte*) &n;
	read(fd, p, sizeof(f64));
	return n;
}

void show(f64 val){
	std::printf("[ %.2f ]\n", val);
}

namespace G {
constexpr usize BUF_SIZE = 8;
usize buf_index = 0;
std::array<f64, BUF_SIZE> weigh_in_buf = {0};
}

int main(int argc, const char** argv){
	if(argc < 2){
		std::fprintf(stderr, "USAGE: display [ITERATIONS]\n");
		return 1;
	}
	usize iter = atoi(argv[1]);
	mkfifo("belt0.fifo", 0666);
	mkfifo("belt1.fifo", 0666);
	f64 acc = 0;
	for(usize i = 0; i < iter; i += 1){
		printf("[[%zu]]\n", i);
		int fd0 = open("belt0.fifo", O_RDONLY);
		int fd1 = open("belt1.fifo", O_RDONLY);
		f64 f0 = read_f64(fd0);
		f64 f1 = read_f64(fd1);
		if((G::buf_index + 2) >= G::BUF_SIZE){
			for(const auto& n : G::weigh_in_buf){ acc += n; }
			show(acc);
			for(auto& n : G::weigh_in_buf){ n = 0; }
			G::buf_index = 0;
		}
		G::weigh_in_buf[G::buf_index] = f0;
		G::weigh_in_buf[G::buf_index + 1] = f1;
		G::buf_index += 2;
		close(fd0);
		close(fd1);
		microsleep(2000000);
	}
	unlink("belt0.fifo");
	unlink("belt1.fifo");
	return 0;
}
