/**
 * @file window.cpp
 * @author Ryan Fong (rybeats@live.com)
 * @brief Window creation
 * @version 0.1
 * @date 2021-05-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/**
 * 05/21/21 - Ryan Fong
 * TODO: Use a new grid made by the server
 * to keep track of position and send delta
 * to change position
 * All positions from the server are
 * subtracted from our pos to get relative
 * pos of other players
 * 
 */

#include "window.h"
#include "raylib.h"
#include "raygui.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

#define MAX_CHUNK 50
//temp
#define SPD 1

window::window(){
   printf("<Filling Windows object>\n");
   width = 800;//temp
   height = 800;//temp
   name = (char*)malloc(strlen("Default"));
   strcpy(name,"Default");
   scale = height/80;
   wdata.width = width;
   wdata.height = height;
   wdata.scale = scale;
   //temp
   stats.name = (char*)malloc(4);
   strcpy(stats.name,"NULL");
   strcpy(stats.id,"000001");
   stats.xp = 0;
   stats.speed = SPD;
   stats.health = 1;
   stats.armor = 0;
   stats.range = 1;
   stats.damage = 1;
   
   bound_len = 0;
   current = -1;
   camera = {{0,0},{0,0},0,1};
}

void window::start(){
   printf("<Initializing...>\n");
   init();
   InitWindow(800,800,"Test");
   SetTargetFPS(60);
   while(!WindowShouldClose()){
      BeginDrawing();
      BeginMode2D(camera);
      ClearBackground(GRAY);
      update();
      EndMode2D();
      EndDrawing();
   }
   exit(EXIT_SUCCESS);
}

void window::init(){
   printf("<Extending size>\n");
   //buttons are spread by 3 scales
   //button 1: purple
   lbl_style(styles[0],"Purple",scale*2,scale/2,GUI_TEXT_ALIGN_CENTER,ColorToInt(PURPLE),{scale,scale,scale*10,scale*2.5f});
   bound_len ++;
   //button 2: blue
   lbl_style(styles[1],"Blue",scale*2,scale/2,GUI_TEXT_ALIGN_CENTER,ColorToInt(BLUE),{scale,scale*4,scale*10,scale*2.5f});
   bound_len++;
   //button 3: white
   lbl_style(styles[2],"White",scale*2,scale/2,GUI_TEXT_ALIGN_CENTER,ColorToInt(WHITE),{scale,scale*7,scale*10,scale*2.5f});
   bound_len++;
   //button 4: red
   lbl_style(styles[3],"Red",scale*2,scale/2,GUI_TEXT_ALIGN_CENTER,ColorToInt(RED),{scale,scale*10,scale*10,scale*2.5f});
   bound_len++;
   me = new player(RED,{width/2.0f,height/2.0f},&stats,&wdata);
}

void window::update(){
   delta = get_delta(scale,SPD);
   me->move(delta);
   me->draw();
   //static layer for self player and buttons
   #pragma omp parallel for
   for(short i = 0; i < bound_len; i++){
      if(draw_lblb(styles[i],BLACK)){
         current = i;
         printf("<%d has been clicked>\n",i);
      }
      // printStyle(labels[i],styles[i]); //debug
   }
   //draw stats
}

