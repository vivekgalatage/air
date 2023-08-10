#include <string>

#include "air/extension.h"

namespace demo::extn {

class StringPolymorphic final
    : public std::string,
      public air::Extension<demo::extn::StringPolymorphic,
                            std::string,
                            air::ExtensionTraits::kPolymorphic> {
 public:
  using std::string::basic_string;

  StringPolymorphic(const std::string& other);

  virtual std::string to_upper() const;
};

StringPolymorphic::StringPolymorphic(const std::string& other)
    : std::string(other) {}

std::string StringPolymorphic::to_upper() const {
  std::string upper_str;
  upper_str.reserve(size());
  for (char c : *this) {
    upper_str.push_back(std::toupper(c));
  }
  return upper_str;
}

}  // namespace demo::extn
