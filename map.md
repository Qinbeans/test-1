# Map Example
``` x,y,direction(0-3),status(-1-1)|... ```
```c++
float x// is x coordinate
float y// is y coordinate
unsigned short int dir// is direction between
//0 and 3 representing if it is looking left,
//right, forwards, or backwards
short int status// is a status for telling
//the client if an object has on, off, or null
//status.  Null meaning impossible state.
```