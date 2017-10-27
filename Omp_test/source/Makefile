# Makefile

# SINGLE, DEBUG, OMP
MODE	= OMP
LEVEL	= -O0

CC	= gcc
OBJS	= hybrid_main.o sub.o all_acc.o acc.o predictor.o corrector.o iteration.o energy.o orbital_elements.o timestep.o angularmomentum.o neighbor.o massflux.o collision.o
CFILE	= hybrid_main.c sub.c all_acc.c acc.c predictor.c corrector.c iteration.c energy.c orbital_elements.c timestep.c angularmomentum.c neighbor.c massflux.c collision.c

ifeq ($(MODE),SINGLE)
	CFLAGS	= $(LEVEL)
endif
ifeq ($(MODE),DEBUG)
	CFLAGS	= -g -O0
endif
ifeq ($(MODE),OMP)
	CFLAGS	= -fopenmp $(LEVEL)
endif


hybrid: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<


$(OBJS): $(CFILE) hybrid.h


clean:
	rm -f $(OBJS) *~ *.dat
