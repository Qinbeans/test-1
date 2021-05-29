#ifndef QSTRING_H
#define QSTRING_H

#include <iostream>

class string{
   public:
      string();
      string(const char* str);
      char* get_str();
      operator char*() const {return str;};
      void operator=(const char* str);
      void operator=(string str);
      char operator[](int index);
      void operator+=(string concat);
      void operator+=(char* concat);
      string operator+(string concat);
      string operator+(char* concat);
      int size();
   private:
      char* str;
      int len;
};

#endif