
all: segv segv2 trap trap2 getpid getpid2

segv: segv_bench.c
	$(CC) -o $@ segv_bench.c -DUSE_SIGINFO $(CFLAGS)
segv2: segv_bench.c
	$(CC) -o $@ segv_bench.c -DUSE_SIGNAL $(CFLAGS)
trap: trap_bench.c
	$(CC) -o $@ trap_bench.c -DUSE_SIGINFO $(CFLAGS)  
trap2: trap_bench.c
	$(CC) -o $@ trap_bench.c -DUSE_SIGNAL $(CFLAGS)
getpid: getpid_bench.c
	$(CC) -o $@ getpid_bench.c -DUSE_SIGINFO $(CFLAGS)
getpid2: getpid_bench.c
	$(CC) -o $@ getpid_bench.c -DUSE_SIGNAL  $(CFLAGS)
