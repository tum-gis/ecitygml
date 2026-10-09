#ifndef ECITYGML_DoubleAttribute_D_HPP
#define ECITYGML_DoubleAttribute_D_HPP

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    struct DoubleAttribute;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A generic attribute with a floating-point value, borrowed from a city model.
 */
class DoubleAttribute {
public:

  inline std::string_view name() const DIPLOMAT_LIFETIME_BOUND;

  inline double value() const;

    inline const ecitygml::capi::DoubleAttribute* AsFFI() const;
    inline ecitygml::capi::DoubleAttribute* AsFFI();
    inline static const ecitygml::DoubleAttribute* FromFFI(const ecitygml::capi::DoubleAttribute* ptr);
    inline static ecitygml::DoubleAttribute* FromFFI(ecitygml::capi::DoubleAttribute* ptr);
    inline static void operator delete(void* ptr);
private:
    DoubleAttribute() = delete;
    DoubleAttribute(const ecitygml::DoubleAttribute&) = delete;
    DoubleAttribute(ecitygml::DoubleAttribute&&) noexcept = delete;
    DoubleAttribute operator=(const ecitygml::DoubleAttribute&) = delete;
    DoubleAttribute operator=(ecitygml::DoubleAttribute&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_DoubleAttribute_D_HPP
