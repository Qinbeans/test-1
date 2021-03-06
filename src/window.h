/**
 * @file window.h
 * @author Ryan Fong (rybeats@live.com)
 * @brief Header for window creation
 * @version 0.1
 * @date 2021-05-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef WINDOW_H
#define WINDOW_H

#define MAX_LEN 100

#include "player.h"
#include <enet/enet.h>

//rather object like, but I don't see any benefits turning this into an object besides neatness

/**
 * @brief Window Object for creating window
 * 
 */
class window{
   public:

      /**
       * @brief Construct a new
       * window object
       * 
       */
      window();

      /**
       * @brief starts the window
       * 
       */
      void start();

      /**
       * @brief intitializes
       * important calculations
       * 
       */
      void init();

      /**
       * @brief Updates window
       * 
       */
      void update();

      bool connected();

      void read_settings();
      
      string new_player();

      void network_poll();

   private:
      Win_data wdata;
      Stats stats;
      player* me;
      string name;
      Vector2 delta;
      float dT;//delta Time checks time it took to finish frame
      Rectangle2D rect_bounds[MAX_LEN];
      Style styles[MAX_LEN];
      short bound_len;
      short current;
      player* players;
      int player_num;
      string settings[MAX_DATA];
      string saved_stats[MAX_DATA];

      ENetHost* client;
      ENetAddress address;
      ENetPeer* peer;
      ENetEvent event;
};

#endif