#pragma once

#include <type_traits>

namespace air {

enum ExtensionTraits {
  kNone = 0,
  kFinal = 1 << 0,
  kPolymorphic = 1 << 1,
  kFinalAndPolymorphic = kFinal | kPolymorphic,
};

template <typename Extn,
          typename Class,
          air::ExtensionTraits traits = air::ExtensionTraits::kNone>
class Extension {
 public:
  constexpr Extension();

  static inline constexpr const Extn& constcast(const Class& instance);

  static inline constexpr Extn& cast(Class& instance);
};

template <typename Extn, typename Class, air::ExtensionTraits traits>
constexpr Extension<Extn, Class, traits>::Extension() {
  using TraitType = typename std::underlying_type<ExtensionTraits>::type;

  static_assert(
      (static_cast<TraitType>(traits) &
       static_cast<TraitType>(ExtensionTraits::kFinalAndPolymorphic)) !=
          static_cast<TraitType>(ExtensionTraits::kFinalAndPolymorphic),
      "An extension Extn can either be final or polymorphic.  Not both.");

  static_assert((static_cast<TraitType>(traits) &
                 static_cast<TraitType>(ExtensionTraits::kFinal)) !=
                        static_cast<TraitType>(ExtensionTraits::kFinal) ||
                    std::is_final<Extn>::value,
                "Extn MUST be final");

  static_assert((static_cast<TraitType>(traits) &
                 static_cast<TraitType>(ExtensionTraits::kFinal)) !=
                        static_cast<TraitType>(ExtensionTraits::kFinal) ||
                    !std::is_polymorphic<Extn>::value,
                "Extn MUST NOT contain any virtual method!");

  static_assert((static_cast<TraitType>(traits) &
                 static_cast<TraitType>(ExtensionTraits::kPolymorphic)) !=
                        static_cast<TraitType>(ExtensionTraits::kPolymorphic) ||
                    std::is_polymorphic<Extn>::value,
                "Extn MUST have at least one virtual method!");

  constexpr auto sizeof_vtable =
      static_cast<TraitType>(traits) &
              static_cast<TraitType>(ExtensionTraits::kPolymorphic)
          ? sizeof(void*)
          : 0;
  static_assert(sizeof(Extn) == sizeof(Class) + sizeof_vtable,
                "The size of Extn MUST be the same as the size of Class.");
}

// static
template <typename Extn, typename Class, air::ExtensionTraits traits>
constexpr const Extn& Extension<Extn, Class, traits>::constcast(
    const Class& instance) {
  static_assert(std::is_base_of<Class, Extn>());
  return static_cast<const Extn&>(instance);
}

// static
template <typename Extn, typename Class, air::ExtensionTraits traits>
constexpr Extn& Extension<Extn, Class, traits>::cast(Class& instance) {
  static_assert(std::is_base_of<Class, Extn>());
  return static_cast<Extn&>(instance);
}

};  // namespace air
