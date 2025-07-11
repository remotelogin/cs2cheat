CC=g++

MAKEFLAGS := --jobs=$(shell nproc)

# TODO: Add more warning flags like -Wall and -Wextra
CFLAGS= -Wno-int-to-pointer-cast -O3 `pkg-config --cflags Qt6Widgets` -fPIC -g

LDFLAGS=-L/usr/X11/lib -lX11 -lXext -lXfixes -lstdc++ `pkg-config --libs Qt6Widgets` #-g 

OBJ_FILES=main.cpp.o hacks/player_info.cpp.o hacks/draw.cpp.o hacks/create_move.cpp.o hacks/esp.cpp.o hacks/aimbot.cpp.o gui/gui.cpp.o hacks/crosshair.cpp.o hacks/fps.cpp.o
OBJS=$(addprefix obj/, $(OBJ_FILES))
BIN=cheat

.PHONY: all clean

#-------------------------------------------------------------------------------

all: $(BIN)

clean:
	rm -f $(OBJS)
	rm -f $(BIN)

#-------------------------------------------------------------------------------

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

obj/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<
