#ifndef ecitygml_GenericAttributeKind_D_HPP
#define ecitygml_GenericAttributeKind_D_HPP

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
namespace capi { struct DoubleAttribute; }
class DoubleAttribute;
namespace capi { struct IntAttribute; }
class IntAttribute;
namespace capi { struct StringAttribute; }
class StringAttribute;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct GenericAttributeKind;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A generic attribute of any kind, borrowed from a city model; get its value with `as_string`,
 * `as_int`, `as_double`, `MeasureAttribute::try_from` or `GenericAttributeSet::try_from`.
 */
class GenericAttributeKind {
public:

  inline std::string_view name() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::StringAttribute* as_string() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::IntAttribute* as_int() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::DoubleAttribute* as_double() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::GenericAttributeKind* AsFFI() const;
    inline ecitygml::capi::GenericAttributeKind* AsFFI();
    inline static const ecitygml::GenericAttributeKind* FromFFI(const ecitygml::capi::GenericAttributeKind* ptr);
    inline static ecitygml::GenericAttributeKind* FromFFI(ecitygml::capi::GenericAttributeKind* ptr);
    inline static void operator delete(void* ptr);
private:
    GenericAttributeKind() = delete;
    GenericAttributeKind(const ecitygml::GenericAttributeKind&) = delete;
    GenericAttributeKind(ecitygml::GenericAttributeKind&&) noexcept = delete;
    GenericAttributeKind operator=(const ecitygml::GenericAttributeKind&) = delete;
    GenericAttributeKind operator=(ecitygml::GenericAttributeKind&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_GenericAttributeKind_D_HPP
