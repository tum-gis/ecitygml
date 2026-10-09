#ifndef ecitygml_MeasureAttribute_D_HPP
#define ecitygml_MeasureAttribute_D_HPP

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
namespace capi { struct Measure; }
class Measure;
namespace capi { struct MeasureAttribute; }
class MeasureAttribute;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct MeasureAttribute;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A generic attribute with a value and unit of measure, borrowed from a city model.
 */
class MeasureAttribute {
public:

  /**
   * The attribute as a measure attribute, or none if it is another kind (Rust has no
   * `as_measure`; it matches `GenericAttributeKind::MeasureAttribute`).
   */
  inline static const ecitygml::MeasureAttribute* try_from(const ecitygml::GenericAttributeKind& attribute DIPLOMAT_LIFETIME_BOUND);

  inline std::string_view name() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::Measure& value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::MeasureAttribute* AsFFI() const;
    inline ecitygml::capi::MeasureAttribute* AsFFI();
    inline static const ecitygml::MeasureAttribute* FromFFI(const ecitygml::capi::MeasureAttribute* ptr);
    inline static ecitygml::MeasureAttribute* FromFFI(ecitygml::capi::MeasureAttribute* ptr);
    inline static void operator delete(void* ptr);
private:
    MeasureAttribute() = delete;
    MeasureAttribute(const ecitygml::MeasureAttribute&) = delete;
    MeasureAttribute(ecitygml::MeasureAttribute&&) noexcept = delete;
    MeasureAttribute operator=(const ecitygml::MeasureAttribute&) = delete;
    MeasureAttribute operator=(ecitygml::MeasureAttribute&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_MeasureAttribute_D_HPP
