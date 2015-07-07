
TARGETS = segv segv2 trap trap2 getpid getpid2\
   rsegv rsegv2 rtrap rtrap2 rgetpid rgetpid2
all: $(TARGETS)

clean:
	rm -f $(TARGETS)


segv: segv_bench.c common.c
	$(CC) -o $@ segv_bench.c -DUSE_SIGINFO $(CFLAGS)
segv2: segv_bench.c common.c
	$(CC) -o $@ segv_bench.c -DUSE_SIGNAL $(CFLAGS)
trap: trap_bench.c common.c
	$(CC) -o $@ trap_bench.c -DUSE_SIGINFO $(CFLAGS)  
trap2: trap_bench.c common.c
	$(CC) -o $@ trap_bench.c -DUSE_SIGNAL $(CFLAGS)
getpid: getpid_bench.c common.c
	$(CC) -o $@ getpid_bench.c -DUSE_SIGINFO $(CFLAGS)
getpid2: getpid_bench.c common.c
	$(CC) -o $@ getpid_bench.c -DUSE_SIGNAL  $(CFLAGS)

rsegv: segv_bench.c common.c
	$(CC) -o $@ segv_bench.c -DUSE_RTCLOCK -DUSE_SIGINFO $(CFLAGS)
rsegv2: segv_bench.c common.c
	$(CC) -o $@ segv_bench.c -DUSE_RTCLOCK -DUSE_SIGNAL $(CFLAGS)
rtrap: trap_bench.c common.c
	$(CC) -o $@ trap_bench.c -DUSE_RTCLOCK -DUSE_SIGINFO $(CFLAGS)  
rtrap2: trap_bench.c common.c
	$(CC) -o $@ trap_bench.c -DUSE_RTCLOCK -DUSE_SIGNAL $(CFLAGS)
rgetpid: getpid_bench.c common.c
	$(CC) -o $@ getpid_bench.c -DUSE_RTCLOCK -DUSE_SIGINFO $(CFLAGS)
rgetpid2: getpid_bench.c common.c
	$(CC) -o $@ getpid_bench.c -DUSE_RTCLOCK -DUSE_SIGNAL  $(CFLAGS)
