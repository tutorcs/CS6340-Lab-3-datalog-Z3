.PRECIOUS: %.ll

TARGETS=ArrayDemo.ReachDef.out Greatest.ReachDef.out ArrayDemo.Liveness.out Greatest.Liveness.out

all: ${TARGETS}

%.bc: %.c
	clang -emit-llvm -c -o $@ $<

%.ReachDef.out: %.bc
	../build/constraint -ReachDef $< > $@ 2> $@.err
%.Liveness.out: %.bc
	../build/constraint -Liveness $< > $@ 2> $@.err

clean:
	rm -f *.bc *.out *.err ${TARGETS}
