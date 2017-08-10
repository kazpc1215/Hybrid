# Makefile

CC	= cc
OBJS	= hybrid_main.o sub.o all_acc.o acc.o predictor.o corrector.o iteration.o energy.o orbital_elements.o timestep.o angularmomentum.o neighbor.o massflux.o
CFILE	= hybrid_main.c sub.c all_acc.c acc.c predictor.c corrector.c iteration.c energy.c orbital_elements.c timestep.c angularmomentum.c neighbor.c massflux.c
FLAG	= -g -O0

hybrid: $(OBJS)
	$(CC) -O3 -o $@ $(OBJS)

debug: $(OBJS)
	$(CC) $(FLAG) -o $@ $(OBJS)

.c.o:
	$(CC) -c $<

$(OBJS): $(CFILE) hybrid.h


clean:
	rm -f $(OBJS) *~ *.dat
