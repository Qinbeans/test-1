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


void lbl_style(Style& style,string name, float font, float spacing,int align, int color, Rectangle2D frame){
   style = {name,font,spacing,align,color,frame};
}

bool draw_lblb(Style style, Color frame_color){
   DrawRectangleRec(style.frame, frame_color);
   GuiSetStyle(DEFAULT,TEXT_SIZE,style.font);
   GuiSetStyle(DEFAULT,TEXT_SPACING,style.spacing);
   GuiSetStyle(LABEL, TEXT_ALIGNMENT, style.align);
   GuiSetStyle(LABEL, TEXT + (guiState*3), style.color);
   return GuiLabelButton(style.frame, style.name.c_str());
}

void draw_lbl(Style style, Color frame_color){
   DrawRectangleRec(style.frame, frame_color);
   GuiSetStyle(DEFAULT,TEXT_SIZE,style.font);
   GuiSetStyle(DEFAULT,TEXT_SPACING,style.spacing);
   GuiSetStyle(LABEL, TEXT_ALIGNMENT, style.align);
   GuiSetStyle(LABEL, TEXT + (guiState*3), style.color);
   GuiLabel(style.frame,style.name.c_str());
}

void draw_txt(Style style, Color frame_color, char* text, int txt_len, bool edit_mode){
   DrawRectangleRec(style.frame, frame_color);
   GuiSetStyle(DEFAULT,TEXT_SIZE,style.font);
   GuiSetStyle(DEFAULT,TEXT_SPACING,style.spacing);
   GuiSetStyle(LABEL, TEXT_ALIGNMENT, style.align);
   GuiSetStyle(LABEL, TEXT + (guiState*3), style.color);
   GuiTextBox(style.frame,text,txt_len,edit_mode);
}

void set_style_name(Style& style, string name){
   style.name = name;
}

void printStyle(Style style){
   printf("Name: %s | Font: %f| Spacing: %f| Align: %d | Color: %d | Rectangle:\n\t{ X: %f| Y: %f | Width: %f | Height: %f }\n",style.name.c_str(),style.font,style.spacing,style.align,style.color,style.frame.x,style.frame.y,style.frame.width,style.frame.height);
}

Vector2 get_delta(float scale, float speed){
   Vector2 delta = {0,0};
   delta.x = ((IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) + GetGamepadAxisMovement(0,GAMEPAD_AXIS_LEFT_X)) * scale * speed;
   delta.y = ((IsKeyDown(KEY_S) - IsKeyDown(KEY_W)) + GetGamepadAxisMovement(0,GAMEPAD_AXIS_LEFT_Y)) * scale * speed;
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

void parse(string strong_data[MAX_DATA], const char delim, string data){
   string temp;
   int out_index = 0;
   for(int i = 0; i < data.size(); i++){
      if(data[i] != delim){
         temp += data[i];
      }
      else{
         strong_data[out_index] = temp;
         out_index++;
         temp = "";
      }
   }
   strong_data[out_index] = temp;
}

void print_stats(Stats stats){
   printf("Stats: %s %s %.2f %.2f %.2f %.2f %.2f %.2f\n",stats.name.c_str(),stats.id.c_str(),stats.xp,stats.speed,stats.health,stats.armor,stats.range,stats.damage);
}
