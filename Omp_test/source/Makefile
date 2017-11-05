# Makefile

# SINGLE, DEBUG, OMP
MODE	= SINGLE

#-O0,-O1,-O2,-O3
LEVEL	= -O3

CC	= gcc
OBJS	= hybrid_main.o sub.o acc.o predictor.o corrector.o iteration.o energy.o orbital_elements.o timestep.o neighbor.o massflux.o collision.o


ifeq ($(MODE),SINGLE)
	CFLAGS	= $(LEVEL)
endif
ifeq ($(MODE),DEBUG)
	CFLAGS	= -g -O0
endif
ifeq ($(MODE),OMP)
	CFLAGS	= -fopenmp $(LEVEL)
endif

CFLAGS += -MD


hybrid: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<


clean:
	rm -f $(OBJS) *~ *.dat *.d

-include *.d
