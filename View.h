#ifndef VIEW_H
#define VIEW_H
#include <regex>
#include <algorithm>
#include <cctype>
#include "Notice.h"
class View: public Notice {

 protected:
 std::string title;
 
 public:
  std::string displayLine(){
   return "========================";
  }

  std::string displayTitle(){
   // "\n\t" to std::string("\n\t") is replaced to fix the issue about 
   // invalid operands to binary expression ('const char[3]' and 'const char[12]')
   return std::string("\n\t") + ANSI_COLOR_GREEN + displayLine() + "\n\t" + title + "\n\t" + displayLine() + "\n" + ANSI_COLOR_RESET;
  }

  void replaceChar(std::string &str, char char_orig, char char_replace){
    replace(str.begin(), str.end(), char_orig, char_replace);
  }

  void toUpperCase(std::string &str){
    transform(str.begin(), str.end(), str.begin(), ::toupper);
  }

  void removeExtraSpaces(std::string& str) {
    // Replace consecutive spaces with a single space
    std::regex regex("\\s+");
    str = std::regex_replace(str, regex, " ");

    // Remove leading and trailing spaces
    str = std::regex_replace(str, std::regex("^\\s+|\\s+$"), "");
  }

  void resetUserScanInput(std::string error_message){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    setErrorNotice(error_message);
  }
};
#endif