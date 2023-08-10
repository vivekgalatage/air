#include <iostream>

#include "string/string_extn.h"
#include "string/string_final_extn.h"
#include "string/string_polymorphic_extn.h"

int main(int argc, char* argv[]) {
  demo::extn::String str1 = std::string("Hello World!!!");
  std::cout << "Original: " << str1 << std::endl;
  std::cout << "String Upper: " << str1.to_upper() << std::endl;

  demo::extn::StringFinal str2 = str1.to_upper();
  demo::extn::StringPolymorphic str3 = str2.to_lower();
  std::cout << "StringFinal Lower: " << str2.to_lower() << std::endl;
  std::cout << "StringPolymorphic Upper: " << str3.to_upper() << std::endl;
  return 0;
}
