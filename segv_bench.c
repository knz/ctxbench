#include "common.c"

int main(int argc, char **argv)
{
    BEGIN_MAIN;

    volatile char* invalid = 0;
    
    BEGIN_LOOP {
	SETUP_SIGNAL(SIGSEGV);

	if (setjmp(rst) == 0)
	{
	    start = rdtsc();
	    *invalid = 123;
	}
    }
    END_LOOP;

    END_MAIN("segv");
}
