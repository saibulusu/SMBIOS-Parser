CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude
CXXFLAGS += -I./include

SRC = $(wildcard src/*.cpp src/structures/*.cpp)

SMBIOS-Parser: $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f SMBIOS-Parser
