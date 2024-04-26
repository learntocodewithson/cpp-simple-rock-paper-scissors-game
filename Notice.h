#ifndef NOTICE_H
#define NOTICE_H
#include "Colors.h"
class Notice {
 
 protected:
 std::string message;

 void setNotice(std::string m, int status = 200){
  if(status == 200){
    message = ANSI_COLOR_GREEN + m + ANSI_COLOR_RESET;
  }else{
    message = ANSI_COLOR_RED + m + ANSI_COLOR_RESET;
  }
 }

 public:
  std::string displayNotice(){
   return message;
  }

  bool hasNotice(){
   return message != "";
  }

  void setSuccessNotice(std::string m){
    setNotice(m);
  }

  void setErrorNotice(std::string m){
    setNotice(m, 500);
  }

  void resetNotice(){
    message = "";
  }
};
#endif