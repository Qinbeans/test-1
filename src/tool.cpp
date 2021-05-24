/**
 * @file tool.cpp
 * @author Ryan Fong (rybeats@live.com)
 * @brief Defined tool functions for the header
 * @version 0.1
 * @date 2021-05-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#define RAYGUI_IMPLEMENTATION
#include "tool.h"
#include "raylib.h"
#include "raygui.h"

void lbl_style(Style& style,const char* name, float font, float spacing,int align, int color, Rectangle2D frame){
   style = {"",font,spacing,align,color,frame};
   style.name = (char*)malloc(sizeof(name));
   strcpy(style.name,name);
}

bool draw_lblb(Style style, Color frame_color){
   DrawRectangleRec(style.frame, frame_color);
   GuiSetStyle(DEFAULT,TEXT_SIZE,style.font);
   GuiSetStyle(DEFAULT,TEXT_SPACING,style.spacing);
   GuiSetStyle(LABEL, TEXT_ALIGNMENT, style.align);
   GuiSetStyle(LABEL, TEXT + (guiState*3), style.color);
   return GuiLabelButton(style.frame, style.name);
}

bool draw_lbl(Style style, Color frame_color){
   DrawRectangleRec(style.frame, frame_color);
   GuiSetStyle(DEFAULT,TEXT_SIZE,style.font);
   GuiSetStyle(DEFAULT,TEXT_SPACING,style.spacing);
   GuiSetStyle(LABEL, TEXT_ALIGNMENT, style.align);
   GuiSetStyle(LABEL, TEXT + (guiState*3), style.color);
   GuiLabel(style.frame,style.name);
}

void set_style_name(Style& style, char* name){
   style.name = (char*)malloc(strlen(name));
   strcpy(style.name,name);
}

void printStyle(Style style){
   printf("Name: %s | Font: %f| Spacing: %f| Align: %d | Color: %d | Rectangle:\n\t{ X: %f| Y: %f | Width: %f | Height: %f }\n",style.name,style.font,style.spacing,style.align,style.color,style.frame.x,style.frame.y,style.frame.width,style.frame.height);
}

Vector2 get_delta(float scale, float speed){
   Vector2 delta = {0,0};
   delta.x = (IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * scale * speed;
   delta.y = (IsKeyDown(KEY_S) - IsKeyDown(KEY_W)) * scale * speed;
   return delta;
}

void move(float& x, float& y, Vector2& delta){
   x+=delta.x;
   y+=delta.y;
}

char* to_string(float num){
   char* str = (char*)malloc(10);//will do max of 10 digits
   sprintf(str,"%f",num);
   return str;
}