COMPILER = g++
CFLAGS1 = -g -Wall
CFLAGS2 = -g -Wall -O1
CFLAGS3 = -g -Wall -O2
SOURCES = ./sigma/sigma-rec.cpp

all: clean no-opt.out opt.out opt2.out

no-opt.out: $(SOURCES)
	$(COMPILER) $(CFLAGS1) $(SOURCES) -o ./bin/no-opt.out

opt.out: $(SOURCES)
	$(COMPILER) $(CFLAGS2) $(SOURCES) -o ./bin/opt1.out

opt2.out: $(SOURCES)
	$(COMPILER) $(CFLAGS3) $(SOURCES) -o ./bin/opt2.out

clean:
	rm -rf *.out *.out.dSYM