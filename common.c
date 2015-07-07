#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <signal.h>
#include <setjmp.h>
#include <stdlib.h>
#include <time.h>

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

#ifdef USE_RTCLOCK
struct timespec end = {0,0}, start = {0,0};
#define SAMPLE_TIME(Var) clock_gettime(CLOCK_MONOTONIC, &Var)
#define TIME_DELTA(Var1, Var2) \
    ((Var1.tv_sec + 1e-9 * Var1.tv_nsec) - (Var2.tv_sec + 1e-9 * Var2.tv_nsec))
#define TimeUnit "nsec"
#else
volatile unsigned long long end = 0, start = 0;
#define SAMPLE_TIME(Var) Var = rdtsc()
#define TIME_DELTA(Var1, Var2)  (1e-9 * (Var1 - Var2))
#define TimeUnit "cycles"
#endif

sigjmp_buf rst;

#ifdef USE_SIGINFO
void handler(int x, siginfo_t* i, void *p)
{
    SAMPLE_TIME(end);
    siglongjmp(rst, 1);
}
#endif

#ifdef USE_SIGNAL
void handler(int unused)
{
    SAMPLE_TIME(end);
    siglongjmp(rst, 1);
}
#endif

#define BEGIN_MAIN \
    int NUM_CALLS = argv[1] ? atoi(argv[1]) : 10000;	\
    int i; \
    double total = 0, min = 0, max = 0;  \
    double delta = 0;			 \
    for (i = 0; i < 100000; i++) \
    { \
    SAMPLE_TIME(start); \
    SAMPLE_TIME(end); \
    double d = TIME_DELTA(end, start); \
    if (d != 0 && (delta == 0 || d < delta)) delta = d; \
    }
    

#define BEGIN_LOOP \
    for (i = 0; i < NUM_CALLS; i++) \
    {

#define END_LOOP \
    double d = TIME_DELTA(end, start);	  \
	if (d == 0) continue; \
        if (min == 0 || d < min) min = d; \
        if (d > max) max = d; \
        total += d; \
    } 

#define END_MAIN(Prog)							\
    printf(Prog " " TimeUnit " %.1lf %.1lf %.1lf %.1lf\n", 1e9*min, 1e9*max, 1e9* total / NUM_CALLS, 1e9 *delta)

#ifdef USE_SIGNAL
#define SETUP_SIGNAL(Sig) signal(Sig, &handler)
#endif

#ifdef USE_SIGINFO
#define SETUP_SIGNAL(Sig)	\
    do {			  \
	struct sigaction sa;	    \
	sigaction(Sig, 0, &sa);	    \
	sigemptyset(&sa.sa_mask);	      \
	sa.sa_sigaction = &handler;	      \
	sa.sa_flags |= SA_SIGINFO; \
	sa.sa_flags &= ~SA_RESETHAND; \
	sigaction(Sig, &sa, 0);		      \
    } while(0)
#endif
