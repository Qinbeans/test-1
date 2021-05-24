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
   private:
      Win_data wdata;
      Stats stats;
      player* me;
      int width;
      int height;
      float scale;
      char* name;
      Camera2D camera;
      Vector2 delta;
      float dT;//delta Time checks time it took to finish frame
      Rectangle2D rect_bounds[MAX_LEN];
      Style styles[MAX_LEN];
      char* labels[MAX_LEN];
      short bound_len;
      short current;
};

#endif