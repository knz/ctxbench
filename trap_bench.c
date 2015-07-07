#include "common.c"

int main(int argc, char **argv)
{
    BEGIN_MAIN;

    BEGIN_LOOP {
	SETUP_SIGNAL(SIGTRAP);

	if (sigsetjmp(rst,1) == 0)
	{
	    SAMPLE_TIME(start);
	    __asm__ __volatile__("int3");
	}
    }
    END_LOOP;

    END_MAIN("trap");
}
