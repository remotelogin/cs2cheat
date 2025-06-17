#include "create_move.hpp"

#include "../xutil.hpp"

#include "aimbot.hpp"
#include <cstdint>

void create_move(pid_t game_pid, Display* move_display, uintptr_t client_address) {
  for (;;) {
    aimbot(game_pid, move_display, client_address);
    
    usleep(1000*1000/250);
  }
}
