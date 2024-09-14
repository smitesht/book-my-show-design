# Variables
CXX = g++

CXXFLAGS = -Wall -std=c++17 -I./seats

DFLAGS = -g

TARGET = bookmyshow.exe

SRCS = main.cpp City.cpp Movie.cpp Theater.cpp Ticket.cpp BookingManager.cpp $(wildcard seats/*.cpp) $(wildcard screen/*.cpp) $(wildcard show/*.cpp) $(wildcard payment/*.cpp)

OBJS = $(SRCS:%.cpp=%.o)

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	@echo ---------------------------------------------
	@echo building $@ ...
	$(CXX) $(CXXFLAGS) $(DFLAGS) -o $@ $^
	@echo $@ built !
	@echo ----------------------------------------------

clean:
	@echo ----------------------------------------------
	@echo cleaning
	-rm -rf *.o
	-rm -rf seats/*.o screen/*.o show/*.o payment/*.o
	-rm $(TARGET)
	-rm -f *~
	@echo project cleaned!
	@echo ----------------------------------------------