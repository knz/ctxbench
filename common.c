#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <signal.h>
#include <setjmp.h>



#ifdef USE_X86
__attribute__((always_inline))
static unsigned long long int rdtsc(void)
{
    unsigned a, d;

    __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));

    return ((unsigned long long)a) | (((unsigned long long)d) << 32);;
}
#endif

#ifdef USE_ARM
__attribute__((always_inline))
static unsigned  rdtsc (void)
{
    unsigned cc;
    asm volatile ("mrc p15, 0, %0, c15, c12, 1" : "=r" (cc));
    return cc;
}
#endif

volatile unsigned long long end = 0, start = 0;
sigjmp_buf rst;

void handler(int x, siginfo_t* i, void *p)
{
    end = rdtsc();
    siglongjmp(rst, 1);
}

#define BEGIN_MAIN \
    int NUM_CALLS = argv[1] ? atoi(argv[1]) : 10000;	\
    int i; \
    unsigned long long int total = 0, min = 0, max = 0; 

#define BEGIN_LOOP \
    for (i = 0; i < NUM_CALLS; i++) \
    {

#define END_LOOP \
	unsigned long long d = end - start; \
        if (min == 0 || d < min) min = d; \
        if (d > max) max = d; \
        total += d; \
    } 

#define END_MAIN(Prog)							\
    printf(Prog " cycles: min %llu max %llu avg %llu\n", min, max, total / NUM_CALLS)

#define SETUP_SIGNAL(Sig)	\
    do {			  \
	struct sigaction sa;	    \
	sigaction(Sig, 0, &sa);	    \
	sigemptyset(&sa.sa_mask);	      \
	sa.sa_sigaction = &handler;	      \
	sa.sa_flags |= SA_SIGINFO|SA_RESTART; \
	sigaction(Sig, &sa, 0);		      \
    } while(0)
    
