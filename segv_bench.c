#include "common.c"

void main(int argc, char **argv)
{
    BEGIN_MAIN;

    BEGIN_LOOP {
	SETUP_SIGNAL(SIGSEGV);

	if (sigsetjmp(rst, 0) == 0)
	{
	    start = rdtsc();
	    *(char*)0 = 123;
	}
    }
    END_LOOP;

    END_MAIN("segv");
}
