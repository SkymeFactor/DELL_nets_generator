#------------------------------------------------------------
#	Variables
#------------------------------------------------------------

# Compiler options
CXX=g++
CXXFLAGS=-g -Wall -std=c++17
LD_FLAGS=-DDEBUG

# Directories
SRC_DIR=src/
INCLUDE_DIR=include/
OBJ_DIR=obj/
BIN_DIR=build/

# Files
SOURCES=$(wildcard $(SRC_DIR)*.cpp)
INCLUDE=-I$(INCLUDE_DIR)
OBJECTS=$(SOURCES:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)
BINARIES=$(BIN_DIR)subnet_gen.elf

# Cleaner
RM=rm -rf

#------------------------------------------------------------
#	Targets
#------------------------------------------------------------

.PHONY: all clean

all: $(OBJECTS) $(BINARIES)

$(OBJECTS): $(SOURCES)
	$(CXX) -c $(CXXFLAGS) $(INCLUDE) $< -o $@ $(LD_FLAGS)

$(BINARIES): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LD_FLAGS)

clean:
	$(RM) $(OBJECTS)
	$(RM) $(BINARIES)
