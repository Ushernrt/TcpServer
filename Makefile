SOURCES:=$(wildcard *.cc)
OBJS:=$(patsubst %.cc, %.o, $(SOURCES))
LIBS:= -lpthread

CXX:=g++

CXXFLAGS:= -std=c++11

EXE:=./server.exe

$(EXE) : $(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS) $(LIBS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)


