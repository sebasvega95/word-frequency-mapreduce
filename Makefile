CXX = g++
CFLAGS = -std=c++11 -O2 -Wall
CLIBS = -lzmqpp -lzmq
LOCAL_FLAGS = -I ~/zmq/include -L ~/zmq/lib

all: mapper partitioner

mapper: mapper.cpp
ifeq ($(C_ENV), local)
	$(CXX) $(CFLAGS) $(LOCAL_FLAGS) mapper.cpp $(CLIBS) -o mapper.out
else
	$(CXX) $(CFLAGS) mapper.cpp $(CLIBS) -o mapper.out
endif

partitioner: partitioner.cpp
ifeq ($(C_ENV), local)
	$(CXX) $(CFLAGS) $(LOCAL_FLAGS) partitioner.cpp $(CLIBS) -o partitioner.out
else
	$(CXX) $(CFLAGS) partitioner.cpp $(CLIBS) -o partitioner.out
endif

clean:
	rm -f *.out
