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
#include <string>//using string since mine caused memory leaking

using std::string;

#ifdef __MACH__
#define GAMEDIR ".2D_Game"
const string OS="mac";
#elif defined(_WIN32) || defined(_WIN64)
#define GAMEDIR "/AppData/LocalLow/2D_Game"
const string OS="win";
#else
#define GAMEDIR ".2Dgame"
const string OS="lin";
#endif


#define MAX_DATA 15

/**
 * @brief carries player stats
 * 
 */
typedef struct Stats{
   string name;
   //6 digit ID, server check if
   //atoi(id) < 0 then it will
   //assign random number for ID
   string id;
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
   string name;
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
 * @brief draws label from style and color
 * 
 * @param style 
 * @param frame_color 
 */
void draw_lbl(Style style, Color frame_color);

/**
 * @brief draws textbox
 * 
 * @param style 
 * @param frame_color 
 * @param text 
 * @param txt_len 
 * @param edit_mode 
 */
void draw_txt(Style style, Color frame_color, char* text, int txt_len, bool edit_mode);

/**
 * @brief Set the style name
 * 
 * @param style 
 * @param name 
 */
void set_style_name(Style& style, string name);

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
void lbl_style(Style& style,string name, float font, float spacing,int align, int color, Rectangle2D frame);

/**
 * @brief Calculates delta value
 * based on speed and scale
 * 
 * @param scale 
 * @param speed 
 * @return Vector2 
 */
Vector2 get_delta(float scale, float speed);

/**
 * @brief moves an pos by delta
 * 
 * @param x 
 * @param y 
 * @param delta 
 */
void move(float& x, float& y, Vector2 delta);

/**
 * @brief makes a string from a float
 * 
 * @param num 
 * @return char* 
 */
char* to_string(float num);

void parse(string strong_data[MAX_DATA], const char delim, string data);

void print_stats(Stats stats);
