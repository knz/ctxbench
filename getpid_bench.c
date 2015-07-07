#include "common.c"

int main(int argc, char **argv)
{
    BEGIN_MAIN;

    BEGIN_LOOP {

	SAMPLE_TIME(start);
	syscall(SYS_getpid);
	SAMPLE_TIME(end);
    }
    END_LOOP;

    END_MAIN("getpid");
}
