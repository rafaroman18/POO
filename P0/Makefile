#MACROS
STD = c++11
CXX = c++
CXXFLAGS = -std=${STD} -g -pedantic -Wall
CPPFLAGS = -DP0 -I../Tests-auto -I.
LDFLAGS = -I../Tests-auto/
VPATH = ../Tests-auto:.
OBJETOS = test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o cadena.o fecha.o

#REGLAS
all: test-P0-auto test-P0-consola

test-P0-auto: $(OBJETOS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@
	
test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: \
	test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp \
	test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp

cadena.o: cadena.cpp cadena.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

fecha.o: fecha.cpp fecha.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

test-P0-consola: test-P0-consola.o fecha.o cadena.o
	$(CXX) $(CXXFLAGS) $^ -o $@

test-P0-consola.o: test-P0-consola.cpp fecha.hpp cadena.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

check: fecha_check cadena_check
	./cadena_check cadena.cpp -- -std=${STD}
	./fecha_check fecha.cpp -- -std=${STD}

fecha_check cadena_check: fecha_check.cpp cadena_check.cpp
	make -f Make_check.mk

clean:
	$(RM) test-P0-auto test-P0-consola $(OBJETOS) test-P0-consola.o
