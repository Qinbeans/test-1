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
#include <iostream>
#include <cstring>

#define MAXDATA 10

/**
 * @brief Player object for all players
 * 
 */
class player{
   public:

      /**
      * @brief Construct a new default
      * player::player object
      * 
      */
      player();
      
      /**
      * @brief Construct a new 
      * player::player object
      * 
      * @param color 
      * @param pos 
      * @param stats 
      * @param window 
      */
      player(Color color, Vector2 pos, Stats* stats, Win_data* window);

      ~player();

      /**
      * @brief Gets the data of player 
      * in the form of char* to send 
      * to server.
      * 
      * @return string
      */
      string get_packet();
      
      /**
      * @brief draws player on screen
      * 
      */
      void draw();

      /**
      * @brief moves player's x and y
      * relative to server's origin
      * 
      * @param delta 
      */
      void move(Vector2 delta);

      /**
      * @brief gets the actual position
      * aka the relative position on
      * the server as a string
      * 
      * @return char* 
      */
      char* get_str_apos();

      /**
       * @brief Get the relative position
       * 
       * @return Vector2 
       */
      Vector2 get_apos() {return pos_act;};

      void set_color(Color color);

      void set_apos(Vector2 pos){pos_act = pos;};

      void set_stats(Stats in){stats = new Stats(in);};

      bool operator==(player p2){return this->stats== p2.stats;};

      Stats get_stats() const {return *stats;};
      
      void draw_outsider();

   private:
      Color color;
      Vector2 pos_act;//position within server.  Same as pos initially
      Vector2 pos;
      Stats* stats;
      Win_data* window;
      float radius;
      Vector2 sword;
      Style apos_sty;//for labels and such
};

#endif