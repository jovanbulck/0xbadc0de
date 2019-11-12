#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>
#include <time.h>
#include <inttypes.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/uio.h>

#define HW_FILE "/app/helloworld.txt"

#define offsetof(st, m) __builtin_offsetof(st, m)


unsigned int total = 0;

#define STRINGIZE_NX(A) #A
#define member_size(type, member) sizeof(((type *)0)->member)
#define PR_OFFSET(st, m) printf("%s: %ld (size %ld)\n", STRINGIZE_NX(m), offsetof(st, m), member_size(st, m) ); total += member_size(st, m);
#define PR_TOTAL(st) printf("--> total = %ld, expected %ld\n\n", total, sizeof(st)); total = 0;

static void handler(int signum)
{
    /* Take appropriate actions for signal delivery */
}

static void foo(char* test)
{
	printf("%s", test);
	volatile fooo[64];
	memset(fooo, 0x41, 64);
}

int main(int argc, char **argv)
{
	printf("sizeof(pollfd) = %ld\n", sizeof(struct pollfd));
    PR_OFFSET(struct pollfd, fd);
    PR_OFFSET(struct pollfd, events);
    PR_OFFSET(struct pollfd, revents);
	PR_TOTAL(struct pollfd);

	printf("sizeof(timespec) = %ld\n", sizeof(struct timespec));
    PR_OFFSET(struct timespec, tv_sec);
    PR_OFFSET(struct timespec, tv_nsec);
	PR_TOTAL(struct timespec);

	printf("sizeof(stat) = %ld\n", sizeof(struct stat));
    PR_OFFSET(struct stat, st_dev);
    PR_OFFSET(struct stat, st_ino);
    PR_OFFSET(struct stat, st_nlink);
    PR_OFFSET(struct stat, st_mode);
    PR_OFFSET(struct stat, st_uid);
    PR_OFFSET(struct stat, st_gid);
    PR_OFFSET(struct stat, __pad0);
    PR_OFFSET(struct stat, st_rdev);
    PR_OFFSET(struct stat, st_size);
    PR_OFFSET(struct stat, st_blksize);
    PR_OFFSET(struct stat, st_blocks);
    PR_OFFSET(struct stat, st_atim);
    PR_OFFSET(struct stat, st_mtim);
    PR_OFFSET(struct stat, st_ctim);
    PR_OFFSET(struct stat, __unused);
	PR_TOTAL(struct stat);
   
    printf("sizeof(sigaction) = %ld\n", sizeof(struct sigaction));
    PR_OFFSET(struct sigaction, __sa_handler);
    PR_OFFSET(struct sigaction, sa_mask);
    PR_OFFSET(struct sigaction, sa_flags);
    PR_OFFSET(struct sigaction, sa_restorer);
	PR_TOTAL(struct sigaction);
	
	printf("sizeof(iovec) = %ld\n", sizeof(struct iovec));
    PR_OFFSET(struct iovec, iov_base);
    PR_OFFSET(struct iovec, iov_len);
	PR_TOTAL(struct iovec);
	
	printf("sizeof(siginfo_t) = %ld\n", sizeof(siginfo_t));
    PR_OFFSET(siginfo_t, si_signo);
    PR_OFFSET(siginfo_t, si_errno);
    PR_OFFSET(siginfo_t, si_code);
    PR_OFFSET(siginfo_t, __si_fields);
	PR_TOTAL(siginfo_t);

	
	
	/*struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; 
	
    if (sigaction(SIGSEGV, &sa, NULL) == -1)
    {
		printf("failed to install sigaction\n");
	}
	else
	{
		printf("successfully installed sigaction\n");
	}*/
	
	sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);

    struct timespec to;
    to.tv_sec = 1;
    to.tv_nsec = 0;
	
	foo("baz bar\n");
	
	siginfo_t info;
	info.si_signo = 0;
	info.si_errno = 0;
	info.si_code = 0;

    int ret = sigtimedwait(&set, &info, &to);

    printf("sigtimedwait() returned %ld, %ld\n", ret, info.si_code);
	
	uint8_t* ptr = (uint8_t*)&info;
	for(unsigned int i = 0; i < sizeof(siginfo_t); i++)
	{
		printf("%c ", ptr[i]);
	}

	printf("\n");
    return 0;
}

