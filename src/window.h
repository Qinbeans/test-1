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

#include "tool.h"

//rather object like, but I don't see any benefits turning this into an object besides neatness

class window{
   public:
      window();
      void start();
      void init();
      void update();
   private:
      float width;
      float height;
      float scale;
      char* name;
      Camera2D camera;
      Vector2 delta;
      Rectangle2D rect_bounds[MAX_LEN];
      Style styles[MAX_LEN];
      char* labels[MAX_LEN];
      short bound_len;
      short current;
};

#endif