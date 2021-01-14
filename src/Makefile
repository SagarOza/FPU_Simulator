CXX	=	g++

INCDIR	=	-I. -I.. -I../include
LIBDIR	=	-L. -L.. -L../lib

PROJECT	=	first_counter
SRCS	=	$(wildcard *.cpp)
OBJS	=	$(SRCS: .cpp=.o)

SYSTEMC_LIBS	=	-Wno-overflow -lm

EXECUTABLE=simx

.PHONY: all build $(EXECUTABLE) clean

all: $(EXECUTABLE)

$(EXECUTABLE):	$(OBJS)
	$(CXX) $(INCDIR) $(LIBDIR) -o $@ $^ $(SYSTEMC_LIBS)

build:
	@mkdir -p bin

clean:
	rm -rf bin $(EXECUTABLE) $(ODIR)/*.o simx $(SIM_DIR)/*.vcd
