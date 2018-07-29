# Project: hw7
# Makefile created by Dev-C++ 4.9.9.2

CPP  = g++
CC   = gcc
RES  = 
OBJ  = ClockChecker.o column.o main.o Plan.o Table.o $(RES)
LINKOBJ  = ClockChecker.o column.o main.o Plan.o Table.o $(RES)
LIBS =  -L"C:/Dev-Cpp/lib"  
INCS =  -I"C:/Dev-Cpp/include" 
CXXINCS =  -I"C:/Dev-Cpp/lib/gcc/mingw32/3.4.2/include"  -I"C:/Dev-Cpp/include/c++/3.4.2/backward"  -I"C:/Dev-Cpp/include/c++/3.4.2/mingw32"  -I"C:/Dev-Cpp/include/c++/3.4.2"  -I"C:/Dev-Cpp/include" 
BIN  = hw7
CXXFLAGS = $(CXXINCS)  
CFLAGS = $(INCS)  
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before hw7 all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "hw7" $(LIBS)

ClockChecker.o: ClockChecker.cpp
	$(CPP) -c ClockChecker.cpp -o ClockChecker.o $(CXXFLAGS)

column.o: column.cpp
	$(CPP) -c column.cpp -o column.o $(CXXFLAGS)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)

Plan.o: Plan.cpp
	$(CPP) -c Plan.cpp -o Plan.o $(CXXFLAGS)

Table.o: Table.cpp
	$(CPP) -c Table.cpp -o Table.o $(CXXFLAGS)
