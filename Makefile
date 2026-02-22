ROM_PATH = roms/SuperMarioLandJUE.gb

CPPC = g++
CFLAGS = -Wall -Wextra -std=c++20 -Iinclude -g

SRCDIR = src
OBJDIR = obj

BIN = gameboy

SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

boot: build
	./$(BIN) $(ROM_PATH)

build: $(OBJS)
	$(CPPC) $(CFLAGS) $(OBJS) -o $(BIN)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CPPC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BIN)

