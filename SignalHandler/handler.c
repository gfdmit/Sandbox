#include <unistd.h>
#include <signal.h>

int main() {
	sigset_t blockmask, oldmask;
	sigfillset(&blockmask);
	sigprocmask(SIG_BLOCK, &blockmask, &oldmask);
	char c;
	while(read(STDIN_FILENO, &c, 1) != -2) {
		write(STDOUT_FILENO, &c, 1);
	}

}
