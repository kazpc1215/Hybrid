# Makefile

# SINGLE, DEBUG, OMP
MODE	= OMP

# -O0,-O1,-O2,-O3
LEVEL	= -O3

CC	= cc
OBJS	= hybrid_main.o sub.o acc.o energy.o orbital_elements.o timestep.o neighbor.o massflux.o collision.o

ifeq ($(MODE),OMP)
# OpenMP option
#OMPOP	= -fopenmp
OMPOP	= -h omp
endif


ifeq ($(MODE),SINGLE)
	CFLAGS	= $(LEVEL)
endif
ifeq ($(MODE),DEBUG)
	CFLAGS	= -g -O0
endif
ifeq ($(MODE),OMP)
	CFLAGS	= $(OMPOP) $(LEVEL)
endif

ifeq ($(CC),gcc)
CFLAGS += -lm -Wall -Wextra -MD
endif


hybrid: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<


clean:
	rm -f $(OBJS) *~ *.dat *.d
	rm -r *.dSYM/ *.dtps/

ifeq ($(CC),gcc)
-include *.d
else
hybrid_main.o: hybrid_main.c hybrid.h func.h
acc.o: acc.c hybrid.h func.h
collision.o: collision.c hybrid.h func.h
energy.o: energy.c hybrid.h func.h
massflux.o: massflux.c hybrid.h func.h
neighbor.o: neighbor.c hybrid.h func.h
orbital_elements.o: orbital_elements.c hybrid.h func.h
sub.o: sub.c hybrid.h func.h
timestep.o: timestep.c hybrid.h func.h
endif
