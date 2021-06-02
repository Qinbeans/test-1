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
 * TODO:(COMPLETE 05/29/21) Use a new grid made by the server
 * to keep track of position and send delta
 * to change position
 * All positions from the server are
 * subtracted from our pos to get relative
 * pos of other players
 * 
 */

#include "window.h"
#include "raygui.h"
#include <omp.h>
#include <cstdlib>
#include <cstring>

#define MAX_CHUNK 50
#define MAX_THREAD 1

//checks player's stats's id
int cmpPlayers(const void* a1, const void* a2){
   player p1 = *(const player*)a1;
   player p2 = *(const player*)a2;
   if(p1.get_stats() == NULL && p1.get_stats() == NULL)
      return 0;
   if(p1.get_stats() == NULL || p1.get_stats()->id < p2.get_stats()->id)
      return -1;
   if(p2.get_stats() == NULL || p1.get_stats()->id > p2.get_stats()->id)
      return 1;
   return 0;
}

window::window(){
   printf("<Enet initialized>\n<Filling Windows object>\n");
   name = "Default";
   omp_set_num_threads(MAX_THREAD);
   bound_len = 0;
   current = 3;
   camera = {{0,0},{0,0},0,1};

   //testing
   //simultaneous multithreading
   // #pragma omp parallel sections
   // {
   //    int thread = omp_get_thread_num();
   //    #pragma omp section
   //    printf("Thread: %d\n",thread);
   //    #pragma omp section
   //    printf("Thread?: %d\n",thread);
   // }
}

void window::start(){
   printf("<Initializing...>\n");
   if(!connected()){
      // exit(EXIT_FAILURE);
   }
   init();
   InitWindow(width,height,name.c_str());
   SetTargetFPS(atoi(settings[3].c_str()));
   if(atoi(settings[0].c_str())){
      ToggleFullscreen();
   }

   while(!WindowShouldClose()){
      BeginDrawing();
      BeginMode2D(camera);
      ClearBackground(GRAY);
      //makes drawing separate from polling
      #pragma omp parallel 
      {
         #pragma omp sections nowait
         {
            #pragma omp section
            network_poll();
            #pragma omp section
            update();
         }
      }
      EndMode2D();
      EndDrawing();
   }
   Close_Window();
   while(enet_host_service(client,&event, 100) > 0){
      switch(event.type){
         case ENET_EVENT_TYPE_RECEIVE:{
            enet_packet_destroy(event.packet);
            break;
         }
         case ENET_EVENT_TYPE_DISCONNECT:{
            printf("<Disconnection Succeeded>");
            break;
         }
      }
   }
   enet_host_destroy(client);
   exit(EXIT_SUCCESS);
}

void window::init(){
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
   bound_len++;\
   me = new player(RED,{width/2.0f,height/2.0f},&stats,&wdata);
}

void window::update(){
   printf("<Updating screen>\n");
   delta = get_delta(scale,me->get_stats()->speed);
   me->move(delta);
   me->draw();
   //static layer for self player and buttons
   if(player_num > 0){
      for(short i = 0; i < player_num; i++){
         // account for distance
         // if(players[i].get_apos().x > 0 && players[i].get_apos().x < width && players[i].get_apos().y > 0 && players[i].get_apos().x < height)
         players[i].draw();
      }
   }
   for(short i = 0; i < bound_len; i++){
      if(draw_lblb(styles[i],BLACK)){
         current = i;
         printf("<%d has been clicked>\n",i);
         switch(current){
            case 0:{
               me->set_color(PURPLE);
               break;
            }
            case 1:{
               me->set_color(BLUE);
               break;
            }
            case 2:{
               me->set_color(WHITE);
               break;
            }
            case 3:{
               me->set_color(RED);
               break;
            }
         }
      }
      // printStyle(labels[i],styles[i]); //debug
   }
   //draw stats
}

bool window::connected(){
   string temp;
   scale = 480/MAX_CHUNK;
   client = enet_host_create(NULL,1,2,0,0);
   if(client == NULL){
      printf("<Bad Client Network, Try Again>\n");
      return false;
   }
   printf("<Client created>\n");
   string base_dir = GAMEDIR;
   if(base_dir == "/AppData/LocalLow/2D_Game"){
      base_dir = getenv("USERPROFILE") + base_dir;
   }
   string setfile = base_dir+"/settings.inline";
   string gamefile = base_dir+"/gamedata.inline";

   //read data
   if(!DirectoryExists(base_dir.c_str())){
      printf("<Game dir:%s does not exists>\n",base_dir.c_str());
   }
   if(!FileExists(setfile.c_str())){
      printf("<Settings does not exists>\n");
      InitWindow(640,480,"Settings");
      int current_mon = GetCurrentMonitor();
      temp = "0 "+std::to_string(GetMonitorWidth(current_mon))+" "+std::to_string(GetMonitorHeight(current_mon))+" 60 67.166.153.136 25570 0 0 0 0\0";
      Close_Window();
      SaveFileText(setfile.c_str(),(char*)temp.c_str());
   }
   if(!FileExists(gamefile.c_str())){
      printf("<Game Data does not exists>\n");
      InitWindow(640,480,"Sign Up");
      temp = new_player();
      Close_Window();
      SaveFileText(gamefile.c_str(),(char*)temp.c_str());
   }
   temp = LoadFileText(setfile.c_str());
   parse(settings,32,temp);
   temp = LoadFileText(gamefile.c_str());
   parse(saved_stats,32,temp);
   stats = {saved_stats[0],saved_stats[1],(float)atof(saved_stats[2].c_str()),(float)atof(saved_stats[3].c_str()),(float)atof(saved_stats[4].c_str()),(float)atof(saved_stats[5].c_str()),(float)atof(saved_stats[6].c_str()),(float)atof(saved_stats[7].c_str())};
   width = (float)atof(settings[1].c_str());
   height = (float)atof(settings[2].c_str());
   scale = height/MAX_CHUNK;
   // printf("Width:%f Height:%f\n",width,height);
   wdata.scale = scale;
   wdata.width = width;
   wdata.height = height;

   enet_address_set_host(&address,settings[4].c_str());
   address.port = stoi(settings[5]);
   peer = enet_host_connect(client,&address,2,0);
   printf("<Checking peer>\n");
   if(peer == NULL){
      printf("<Bad Peer, Try Again>\n");
      return false;
   }
   printf("<Peer Connection Success>\n");
   if(enet_host_service(client, &event,1000) > 0){
      switch(event.type){
         case ENET_EVENT_TYPE_CONNECT:{
            printf("<Connected to %d:%d>\n",address.host,address.port);
            string data = "0 "+me->get_packet();
            ENetPacket* user = enet_packet_create(data.c_str(), data.size()+1,ENET_PACKET_FLAG_RELIABLE);
            enet_peer_send(peer, 0, user);
            return true;
         }
         default:{
            enet_peer_reset(peer);
            printf("<Connection to %d:%d failed>\n",address.host,address.port);
            break;
         }
      }
   }
   enet_peer_disconnect(peer, 0);
   // print_stats(stats);
   return false;
}

string window::new_player(){
   SetTargetFPS(30);
   float buffer = scale * 2;
   string inputs;
   bool submit = false;
   short box_num = 3;
   char* temp[box_num-1];
   float width_box = scale*20;
   float height_box = scale*4;
   float box_x = scale*20;
   float box_ys[] = {scale,scale*7,scale*13,scale*19,scale*25,scale*31}; //last is submit button
   Style menu_styles[box_num];
   short curr_box = 0;//0-4
   for(int i = 0; i < box_num; i++){
      temp[i]=(char*)malloc(10);
      if(temp[i]!=NULL){
         switch(i){
            case 0:{
               lbl_style(menu_styles[i],std::to_string(i),scale*3,scale/2,GUI_TEXT_ALIGN_LEFT,ColorToInt(WHITE),{box_x,box_ys[i],width_box,height_box});
               strcpy(temp[i],"Username");
               break;
            }case 1:{
               lbl_style(menu_styles[i],std::to_string(i),scale*3,scale/2,GUI_TEXT_ALIGN_LEFT,ColorToInt(WHITE),{box_x,box_ys[i],width_box,height_box});
               strcpy(temp[i],"0000ID");
               break;
            }case 2:{
               lbl_style(menu_styles[i],"Submit",scale*3,scale/2,GUI_TEXT_ALIGN_CENTER,ColorToInt(WHITE),{box_x,box_ys[i],scale*10,height_box});
            }
         }
      }
   }
   while(!WindowShouldClose()&&!submit){
      BeginDrawing();
      ClearBackground(GRAY);
      for(int i = 0; i < box_num;i++){
         //check event for pressing box
         if(i < 2){
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(),{box_x,box_ys[i],width_box,height_box})){
               curr_box = i;
            }
            if(i==1 && strlen(temp[i])>6){
               string hold = temp[i];
               hold = hold.substr(hold.size()-6,6);
               temp[i] = (char*)malloc(7);
               strcpy(temp[i],hold.c_str());
            }else if(i==1 && strlen(temp[i])<6){
               string hold = temp[i];
               while(hold.size()<6){
                  hold = "0" + hold;
               }
               temp[i] = (char*)malloc(7);
               strcpy(temp[i],hold.c_str());
            }
            draw_txt(menu_styles[i],BLACK,temp[i],20,curr_box==i);
         }else{
            submit = draw_lblb(menu_styles[i],BLACK);
         }
      }
      EndDrawing();
   }
   inputs+=temp[0];
   inputs+=" ";
   inputs+=temp[1];
   inputs+=" 0.0 1.0 0.5 0.1 0 0 0\0";
   free(temp[0]);
   free(temp[1]);
   return inputs;
}

void window::network_poll(){
   printf("<Polling network>\n");
   int status = enet_host_service(client, &event, 10);
   while(status > 0){
      switch(event.type){
         case ENET_EVENT_TYPE_RECEIVE:{
            int len = 10;
            player* temp = nullptr;
            string parsed_data[len];
            string packet_data = (char*)event.packet->data;
            parse(parsed_data,32,packet_data);
            Color other_color = GetColor(stoi(parsed_data[9]));
            Vector2 other_pos = {stof(parsed_data[7])*scale,stof(parsed_data[8])*scale};
            Stats other_stats = {parsed_data[1],parsed_data[2],stof(parsed_data[3]),stof(parsed_data[4]),stof(parsed_data[5]),stof(parsed_data[6])};
            player other_p(other_color,{0,0},&other_stats,&wdata);
            //search for name in players
            if(parsed_data[0] == "2" && player_num != 0){
               printf("<%s has left>",parsed_data[1].c_str());
               //use search alg to find player with name
               //might need iostream to overload function
               temp = (player*)bsearch(&other_p,players,player_num,sizeof(player),cmpPlayers);
               if(temp!=NULL){//if the search has a result then erase
                  delete temp;
                  temp = nullptr;
               }
               break;
            }
            if(other_stats.id == me->get_stats()->id){
               break;
            }
            if(player_num > 1){//lets not waste precious processing power
               qsort(players,player_num,sizeof(player),cmpPlayers);
               temp = (player*)bsearch(&other_p,players,player_num,sizeof(player),cmpPlayers);
               if(temp != NULL){
                  printf("<Player exists>\n");
                  temp->set_apos(other_pos);
                  temp->set_color(other_color);
                  temp->set_stats(other_stats);
               }else{
                  //set content of address to this value
                  *temp = other_p;
                  temp->set_apos(other_pos);
               }
            }
         }
         case ENET_EVENT_TYPE_DISCONNECT:{break;}
         case ENET_EVENT_TYPE_NONE:{
            printf("<Nothing>\n");
            break;
         }
      }
      status = enet_host_service(client, &event, 10);
   }
}
