#ifndef ecitygml_GenericAttributeSet_D_HPP
#define ecitygml_GenericAttributeSet_D_HPP

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"

namespace ecitygml {
namespace capi { struct GenericAttributeKind; }
class GenericAttributeKind;
namespace capi { struct GenericAttributeKindIterator; }
class GenericAttributeKindIterator;
namespace capi { struct GenericAttributeSet; }
class GenericAttributeSet;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct GenericAttributeSet;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A named set of generic attributes, borrowed from a city model.
 */
class GenericAttributeSet {
public:

  /**
   * The attribute as a set, or none if it is another kind (Rust has no `as_set`; it matches
   * `GenericAttributeKind::GenericAttributeSet`).
   */
  inline static const ecitygml::GenericAttributeSet* try_from(const ecitygml::GenericAttributeKind& attribute DIPLOMAT_LIFETIME_BOUND);

  inline std::string_view name() const DIPLOMAT_LIFETIME_BOUND;

  inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> generic_attributes() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::GenericAttributeSet* AsFFI() const;
    inline ecitygml::capi::GenericAttributeSet* AsFFI();
    inline static const ecitygml::GenericAttributeSet* FromFFI(const ecitygml::capi::GenericAttributeSet* ptr);
    inline static ecitygml::GenericAttributeSet* FromFFI(ecitygml::capi::GenericAttributeSet* ptr);
    inline static void operator delete(void* ptr);
private:
    GenericAttributeSet() = delete;
    GenericAttributeSet(const ecitygml::GenericAttributeSet&) = delete;
    GenericAttributeSet(ecitygml::GenericAttributeSet&&) noexcept = delete;
    GenericAttributeSet operator=(const ecitygml::GenericAttributeSet&) = delete;
    GenericAttributeSet operator=(ecitygml::GenericAttributeSet&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_GenericAttributeSet_D_HPP
