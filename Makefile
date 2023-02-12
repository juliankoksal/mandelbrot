# VARIABLES

CXX = g++
CXXFLAGS = -std=c++20 -I/opt/homebrew/include -Ofast
LDLIBS = -L/opt/homebrew/lib -lglfw -framework opengl

MAIN = Main
MAIN_OBJ = $(patsubst %,target/%.o,$(MAIN))
OBJ = $(patsubst src/%.cpp,target/%.o,$(wildcard src/*.cpp))
MKDIR_P = @ mkdir -p $(@D)

# SPECIAL TARGETS

.SECONDARY: $(OBJ)

.PHONY: clean cleanout cleanobj

# EXECUTABLES

all: $(MAIN)

%: $(filter-out $(MAIN_OBJ),$(OBJ)) target/%.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

# OBJECTS

target/%.o: src/%.cpp
	$(MKDIR_P)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(wildcard target/*.d)

# PHONY

clean: cleanout cleanobj

cleanout:
	rm -f $(MAIN)

cleanobj:
	rm -rf target

