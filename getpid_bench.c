#include "common.c"

int main(int argc, char **argv)
{
    BEGIN_MAIN;

    BEGIN_LOOP {

	start = rdtsc();
	syscall(SYS_getpid);
	end = rdtsc();
    }
    END_LOOP;

    END_MAIN("getpid");
}
