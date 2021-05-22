/**
 * @file player.h
 * @author Ryan Fong (rybeats@live.com)
 * @brief Player header
 * @version 0.1
 * @date 2021-05-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "tool.h"
#include <cstring>

#define MAXDATA 10

class player{
   public:
      player();
      player(Color color, Vector2 pos, Stats* stats, Win_data* window);
      char* get_packet();
      void draw();
   private:
      Color color;
      Vector2 pos;
      Stats* stats;
      Win_data* window;
};

#endif