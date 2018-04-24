#MACROS
STD = c++11
CXX = c++
CXXFLAGS = -std=${STD} -g -pedantic -Wall
CPPFLAGS = -DP1 -I../Tests-auto -I.
LDFLAGS = -I../Tests-auto/
VPATH = ../Tests-auto:.
OBJETOS = test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o cadena.o fecha.o
CHCK = fecha_check.cpp cadena_check.cpp
TST = test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp test-auto.cpp
TSTOBJ = $(TST:.cpp=.o)
EXE = test-P1-auto test-P1-consola
#REGLA
all: $(EXE)

test-P1-auto: $(OBJETOS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

$(TSTOBJ): $(TST)

cadena.o fecha.o: cadena.cpp fecha.cpp

test-P1-consola: test-P1-consola.o fecha.o cadena.o
	$(CXX) $(CXXFLAGS) $^ -o $@

test-P1-consola.o: test-P1-consola.cpp

check: fecha_check cadena_check
	./cadena_check cadena.cpp -- -std=${STD}
	./fecha_check fecha.cpp -- -std=${STD}

fecha_check cadena_check: $(CHCK)
	make -f Make_check.mk

clean:
	$(RM) $(EXE) $(OBJETOS) test-P1-consola.o
