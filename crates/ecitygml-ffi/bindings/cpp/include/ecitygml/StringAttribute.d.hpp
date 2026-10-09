#ifndef ecitygml_StringAttribute_D_HPP
#define ecitygml_StringAttribute_D_HPP

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
namespace capi {
    struct StringAttribute;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A generic attribute with a text value, borrowed from a city model.
 */
class StringAttribute {
public:

  inline std::string_view name() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::StringAttribute* AsFFI() const;
    inline ecitygml::capi::StringAttribute* AsFFI();
    inline static const ecitygml::StringAttribute* FromFFI(const ecitygml::capi::StringAttribute* ptr);
    inline static ecitygml::StringAttribute* FromFFI(ecitygml::capi::StringAttribute* ptr);
    inline static void operator delete(void* ptr);
private:
    StringAttribute() = delete;
    StringAttribute(const ecitygml::StringAttribute&) = delete;
    StringAttribute(ecitygml::StringAttribute&&) noexcept = delete;
    StringAttribute operator=(const ecitygml::StringAttribute&) = delete;
    StringAttribute operator=(ecitygml::StringAttribute&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_StringAttribute_D_HPP
