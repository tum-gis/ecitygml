#ifndef ECITYGML_IntAttribute_D_HPP
#define ECITYGML_IntAttribute_D_HPP

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
    struct IntAttribute;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A generic attribute with an integer value, borrowed from a city model.
 */
class IntAttribute {
public:

  inline std::string_view name() const DIPLOMAT_LIFETIME_BOUND;

  inline int64_t value() const;

    inline const ecitygml::capi::IntAttribute* AsFFI() const;
    inline ecitygml::capi::IntAttribute* AsFFI();
    inline static const ecitygml::IntAttribute* FromFFI(const ecitygml::capi::IntAttribute* ptr);
    inline static ecitygml::IntAttribute* FromFFI(ecitygml::capi::IntAttribute* ptr);
    inline static void operator delete(void* ptr);
private:
    IntAttribute() = delete;
    IntAttribute(const ecitygml::IntAttribute&) = delete;
    IntAttribute(ecitygml::IntAttribute&&) noexcept = delete;
    IntAttribute operator=(const ecitygml::IntAttribute&) = delete;
    IntAttribute operator=(ecitygml::IntAttribute&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_IntAttribute_D_HPP
