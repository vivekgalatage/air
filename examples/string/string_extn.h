#include <string>

#include "air/extension.h"

namespace demo::extn {

class String : public std::string,
               public air::Extension<demo::extn::String, std::string> {
 public:
  using std::string::basic_string;

  String(const std::string& other);

  std::string to_upper() const;
};

String::String(const std::string& other) : std::string(other) {}

std::string String::to_upper() const {
  std::string upper_str;
  upper_str.reserve(size());
  for (char c : *this) {
    upper_str.push_back(std::toupper(c));
  }
  return upper_str;
}

}  // namespace demo::extn
