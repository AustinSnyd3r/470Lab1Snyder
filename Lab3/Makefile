# Use gcc with warn all flag. 
CC = gcc
CFLAGS = -Wall

# set targets
all: RR SJF

# Compile for round robin
RR: RR_inital.c 
	$(CC) $(CFLAGS) -o RR RR_inital.c 

# Compile for Shortest job first (premptive version)
SJF: SJF_inital.c
	$(CC) $(CFLAGS) -o SJF SJF_inital.c

# Run the targets
run_rr: RR
	./RR

run_sjf: SJF
	./SJF

# clean up
clean:
	rm -f RR SJF
