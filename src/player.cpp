#include "player.h"
#include "raygui.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iomanip>


player::player(){
   color = BLACK;
   pos = {0,0};
   pos_act = pos;
   radius = 1;
}


player::player(Color color, Vector2 pos, Stats* stats, Win_data* window){
   this->color = color;
   radius = window->scale/2;
   this->pos = {pos.x-radius,pos.y-radius};
   pos_act = {0,0};
   this->stats = stats;
   this->window = window;
   char* temp = get_str_apos();
   lbl_style(apos_sty,temp,window->scale,window->scale/4,GUI_TEXT_ALIGN_CENTER,ColorToInt(GREEN),{window->width-window->scale*11,window->scale*2.5f,window->scale*10,window->scale*1.5f});
   free(temp);
}

player::~player(){
   delete stats;
   delete window;
   color = GetColor(-1);
   pos = {};
   pos_act = {};
   radius = -1;
   apos_sty = {};
}

void player::move(Vector2 delta){
   ::move(pos_act.x,pos_act.y,delta);
}

void player::draw(){
   // printf("(%f,%f),radius:%f\n",pos.x,pos.y,radius);
   // printf("<W:%d H:%d S:%f>\n",window->width,window->height,window->scale);
   pos.x=window->width/2.0f;
   pos.y=window->height/2.0f;
   radius=window->scale/2;
   DrawCircleV(pos,radius,color);
   set_sty_font(apos_sty,window->scale);
   set_sty_spacing(apos_sty,window->scale/4);
   set_sty_rect(apos_sty,{window->width-window->scale*11,window->scale*2.5f,window->scale*10,window->scale*1.5f});
   char* temp = get_str_apos();
   set_style_name(apos_sty,temp);
   free(temp);
   draw_lbl(apos_sty,BLACK);
}

char* player::get_str_apos(){
   //some idiot will break this i swear, jumping off the map will seg fault
   char* str = (char*)malloc(1000);//might want to think about making this dynamic somehow
   sprintf(str,"(%.1f,%.1f)",pos_act.x/window->scale,pos_act.y/window->scale);
   return str;
}

void player::set_color(Color color){
   this->color = color;
}

string player::get_packet(){
   return stats->name+" "+string(stats->id)+" "+std::to_string(stats->xp)+" "+std::to_string(stats->health)+" "+std::to_string(stats->speed)+" "+std::to_string(stats->range)+" "+std::to_string(pos_act.x/window->scale)+" "+std::to_string(pos_act.y/window->scale)+" "+std::to_string(ColorToInt(color));
}