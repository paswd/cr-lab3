FLAGS=-pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm -std=c++11 -O2
COMPILLER=g++

all: start

start: main.o ellipsecurve.o
	$(COMPILLER) $(FLAGS) -o ellicurve main.o ellipsecurve.o

main.o: main.cpp
	$(COMPILLER) -c $(FLAGS) main.cpp

ellipsecurve.o: ellipsecurve.cpp
	$(COMPILLER) -c $(FLAGS) ellipsecurve.cpp

clean:
	@-rm -f *.o *.gch *.dat elipcurve
	@echo "Clean success"
