#------------------------------------------------------------
#	Variables
#------------------------------------------------------------

# Compiler options
CXX=g++
CXXFLAGS=-g -Wall -std=c++17
LD_FLAGS=

# Directories
SRC_DIR=src/
INCLUDE_DIR=include/
TEST_DIR=tests/
OBJ_DIR=obj/
BIN_DIR=build/

# Files
SOURCES=$(wildcard $(SRC_DIR)*.cpp)
INCLUDE=-I$(INCLUDE_DIR)
OBJECTS=$(SOURCES:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)
BINARIES=$(BIN_DIR)subnet_gen.elf

# Test files
TEST_SRC=$(wildcard $(TEST_DIR)*.cpp)
TEST_OBJ=$(TEST_SRC:$(TEST_DIR)%.cpp=$(OBJ_DIR)test/%.o)
TEST_BIN=$(BIN_DIR)test_subnet_gen.elf

# Cleaner
RM=rm -rf

#------------------------------------------------------------
#	Targets
#------------------------------------------------------------

.PHONY: all clean

all: $(OBJECTS) $(BINARIES)

test: all $(TEST_OBJ) $(TEST_BIN)

$(OBJECTS): $(SOURCES)
	$(CXX) -c $(CXXFLAGS) $(INCLUDE) $< -o $@ $(LD_FLAGS)

$(BINARIES): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LD_FLAGS)

$(TEST_OBJ): $(TEST_SRC)
	$(CXX) -c $(CXXFLAGS) $(INCLUDE) $< -o $@ $(LD_FLAGS)

$(TEST_BIN): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $< -o $(TEST_BIN) $(LD_FLAGS)

clean:
	$(RM) $(OBJECTS)
	$(RM) $(TEST_OBJ)
	$(RM) $(BINARIES)
	$(RM) $(TEST_BIN)
