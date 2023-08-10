#include <string>

#include "air/extension.h"

namespace demo::extn {

class StringFinal final : public std::string,
                          public air::Extension<demo::extn::StringFinal,
                                                std::string,
                                                air::ExtensionTraits::kFinal> {
 public:
  using std::string::basic_string;

  StringFinal(const std::string& other);

  std::string to_lower() const;
};

StringFinal::StringFinal(const std::string& other) : std::string(other) {}

std::string StringFinal::to_lower() const {
  std::string upper_str;
  upper_str.reserve(size());
  for (char c : *this) {
    upper_str.push_back(std::tolower(c));
  }
  return upper_str;
}

}  // namespace demo::extn
