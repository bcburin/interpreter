#include "helpers.h"

bool starts_with(std::string str, std::string substr) { return str.find(substr)==0; }

std::string trim(std::string str) {
  // Check for empty string
  if(str == "") return str;
  // Trim start of string
  while(str[0] == ' ') str = str.substr(1, str.size()-1);
  // Trim end of string
  while(str[str.size()-1] == ' ') str = str.substr(0, str.size()-1);
  return str;
}