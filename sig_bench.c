#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <signal.h>
#include <setjmp.h>

#define NUM_CALLS 10000

inline unsigned long long int rdtsc(void)
{
    unsigned a, d;

    __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));

    return ((unsigned long long)a) | (((unsigned long long)d) << 32);;
}

volatile unsigned long long end = 0, start = 0;
volatile jmp_buf rst;

void handler(int x)
{
    end = rdtsc();
    longjmp(rst, 1);
}

void main()
{
    int i;
    int id;
    unsigned long long int total, min, max;
    volatile char *invalid = 0;
    struct sigaction sa;

    sigaction(SIGSEGV, 0, &sa);
    sa.sa_handler = &handler;
    sa.sa_flags &= ~SA_RESETHAND;
    sigaction(SIGSEGV, &sa, 0);

    max = 0;
    min = 0;
    total = 0;

    for (i = 0; i < NUM_CALLS; i++)
    {
	printf("YOO\n");
	if (setjmp(rst) == 0)
	{
	    start = rdtsc();
	    *invalid = 123;
	}
	printf("YAY\n");

	unsigned long long d = end - start;
        if (min == 0 || d < min) min = d;
        if (d > max) max = d;
        total += d;
    }

    printf("segv cycles: min %llu max %llu avg %llu\n", min, max, total / NUM_CALLS);

}
