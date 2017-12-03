# Makefile

# SINGLE, DEBUG, OMP
MODE	= DEBUG

#-O0,-O1,-O2,-O3
LEVEL	= -O3

CC	= gcc
OBJS	= hybrid_main.o sub.o acc.o energy.o orbital_elements.o timestep.o neighbor.o massflux.o collision.o


ifeq ($(MODE),SINGLE)
	CFLAGS	= $(LEVEL)
endif
ifeq ($(MODE),DEBUG)
	CFLAGS	= -g -O0
endif
ifeq ($(MODE),OMP)
	CFLAGS	= -fopenmp $(LEVEL)
endif

CFLAGS += -lm -Wall -Wextra -MD



hybrid: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<


clean:
	rm -f $(OBJS) *~ *.dat *.d
	rm -r *.dSYM/ *.dtps/

-include *.d
