/**
 * @file tool.h
 * @author Ryan Fong (rybeats@live.com)
 * @brief File full of tools to help the
 * game including objects I deem too
 * unimportant to make into classes
 * @version 0.1
 * @date 2021-05-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "raylib.h"

#ifdef __MACH__
#define GAMEDIR ".2D_Game"
#elif defined(_WIN32) || defined(_WIN64)
#define GAMEDIR "/AppData/LocalLow/2D_Game"
#else
#define GAMEDIR ".2Dgame"
#endif

/**
 * @brief carries player stats
 * 
 */
typedef struct Stats{
   char* name;
   //6 digit ID, server check if
   //atoi(id) < 0 then it will
   //assign random number for ID
   char id[6];
   float xp;//xp
   float speed;//spd
   float health;//hp
   float armor;//arm
   float range;//rng
   float damage;//dps
}Stats;

/**
 * @brief carries window data so we
 * lessen the amount of parameters
 * needed
 * 
 */
typedef struct Win_data{
   int width;
   int height;
   float scale;
}Win_data;

/**
 * @brief Carries the style used
 * for buttons, but not used
 * exclusively for buttons
 * 
 */
typedef struct Style{
   char* name;
   float font;
   float spacing;
   int align;
   int color;
   Rectangle2D frame;
}Style;

/**
 * @brief draws the label button by
 * declaring the styles then drawing
 * the button
 * 
 * @param style 
 * @param frame_color 
 * @return true 
 * @return false 
 */
bool draw_lblb(Style style, Color frame_color);

/**
 * @brief prints the style for debugging
 * 
 * @param style 
 */
void printStyle(Style style);

/**
 * @brief fills the style with necessary content
 * 
 * @param style 
 * @param name 
 * @param font 
 * @param spacing 
 * @param align 
 * @param color 
 * @param frame 
 */
void lbl_style(Style& style,const char* name, float font, float spacing,int align, int color, Rectangle2D frame);

Vector2 get_delta(float scale, float speed);

void move(float& x, float& y, Vector2& delta);