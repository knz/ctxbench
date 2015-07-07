#include "common.c"

int main(int argc, char **argv)
{
    BEGIN_MAIN;

    BEGIN_LOOP {
	SETUP_SIGNAL(SIGTRAP);

	if (sigsetjmp(rst,1) == 0)
	{
	    SAMPLE_TIME(start);
#ifdef USE_X86
  __asm__ __volatile__("int3");
#endif

#ifdef USE_ARM
  __asm__ __volatile__("bkpt");
#endif
	}
    }
    END_LOOP;

    END_MAIN("trap");
}
