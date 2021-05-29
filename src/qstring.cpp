#include "qstring.h"
#include <cstring>
#include <cstdlib>

string::string(){
   len=0;
   str=(char*)malloc(0);
}

string::string(const char* str){
   len = strlen(str);
   this->str=(char*)malloc(len);
   strcpy(this->str,str);
}

string string::operator+(string concat){
   int temp_size = concat.len + len;
   char temp[temp_size];
   strcat(temp,str);
   strcat(temp,concat.str);
   return string(temp);
}

string string::operator+(char* concat){
   int temp_size = strlen(concat) + len;
   char temp[temp_size];
   strcat(temp,str);
   strcat(temp,concat);
   return string(temp);
}

void string::operator+=(string concat){
   int temp_size = concat.len + len;
   char temp[temp_size];
   strcat(temp,str);
   strcat(temp,concat.str);
   str = (char*)malloc(temp_size);
   strcpy(str,temp);
}

void string::operator+=(char* concat){
   int temp_size = strlen(concat) + len;
   char temp[temp_size];
   strcat(temp,str);
   strcat(temp,concat);
   str = (char*)malloc(temp_size);
   strcpy(str,temp);
}

void string::operator=(string str){
   len = str.len;
   this->str=(char*)malloc(len);
   strcpy(this->str,str.str);
}

void string::operator=(const char* str){
   len = strlen(str);
   this->str=(char*)malloc(len);
   strcpy(this->str,str);
}

char string::operator[](int index){
   return str[index];
}

char* string::get_str(){
   return str;
}

int string::size(){
   return len;
}