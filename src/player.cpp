#include "player.h"

/**
 * @brief Gets the data of player 
 * in the form of char* to send 
 * to server.
 * 
 * @return char* 
 */
char* player::get_packet(){
   return nullptr;
}

/**
 * @brief Construct a new default
 * player::player object
 * 
 */
player::player(){
   color = BLACK;
   pos = {0,0};
}

player::player(Color color, Vector2 pos, Stats* stats, Win_data* window){
   this->color = color;
   this->pos = pos;
   this->stats = stats;
   this->window = window;
}
