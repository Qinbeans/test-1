#include "window.h"
#include <enet/enet.h>

int main(){
   if(enet_initialize() != 0){
      printf("<Could not start ENet>");
      exit(EXIT_FAILURE);
   }
   atexit(enet_deinitialize);
   window win;
   win.start();
   return 0;
}