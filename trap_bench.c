#include "common.c"

int main(int argc, char **argv)
{
    BEGIN_MAIN;

    BEGIN_LOOP {
	SETUP_SIGNAL(SIGTRAP);

	if (setjmp(rst) == 0)
	{
	    start = rdtsc();
	    __asm__ __volatile__("int3");
	}
    }
    END_LOOP;

    END_MAIN("trap");
}
