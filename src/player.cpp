#include "player.h"
#include "raygui.h"
#include <stdio.h>
#include <stdlib.h>


char* player::get_packet(){
   return nullptr;
}


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
   pos_act = pos;
   this->stats = stats;
   this->window = window;
   lbl_style(apos_sty,get_str_apos(),window->scale,window->scale/4,GUI_TEXT_ALIGN_CENTER,ColorToInt(GREEN),{window->width-window->scale*11,window->scale*2.5f,window->scale*10,window->scale*1.5f});
}

void player::move(Vector2 delta){
   ::move(pos_act.x,pos_act.y,delta);
}

void player::draw(){
   // printf("(%f,%f),radius:%f\n",pos.x,pos.y,radius);
   DrawCircleV(pos,radius,color);
   set_style_name(apos_sty,get_str_apos());
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
   // if(ColorToInt(color)==ColorToInt(RED)){
   //    printf("red");
   // }else if(ColorToInt(color)==ColorToInt(BLUE)){
   //    printf("blue");
   // }else if(ColorToInt(color)==ColorToInt(PURPLE)){
   //    printf("purple");
   // }else if(ColorToInt(color)==ColorToInt(WHITE)){
   //    printf("white");
   // }
}