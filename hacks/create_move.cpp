#include "create_move.hpp"

#include "../xutil.hpp"

#include "aimbot.hpp"

void create_move(pid_t game_pid, Display* move_display) {
  for (;;) {
    aimbot(game_pid, move_display);
    
    usleep(1000*1000/250);
  }
}
