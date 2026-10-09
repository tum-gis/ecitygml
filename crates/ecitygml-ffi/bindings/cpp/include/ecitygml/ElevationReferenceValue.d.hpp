#ifndef ecitygml_ElevationReferenceValue_D_HPP
#define ecitygml_ElevationReferenceValue_D_HPP

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
namespace capi { struct Code; }
class Code;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct ElevationReferenceValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `highReference`/`lowReference` property of a Height.
 */
class ElevationReferenceValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::ElevationReferenceValue* AsFFI() const;
    inline ecitygml::capi::ElevationReferenceValue* AsFFI();
    inline static const ecitygml::ElevationReferenceValue* FromFFI(const ecitygml::capi::ElevationReferenceValue* ptr);
    inline static ecitygml::ElevationReferenceValue* FromFFI(ecitygml::capi::ElevationReferenceValue* ptr);
    inline static void operator delete(void* ptr);
private:
    ElevationReferenceValue() = delete;
    ElevationReferenceValue(const ecitygml::ElevationReferenceValue&) = delete;
    ElevationReferenceValue(ecitygml::ElevationReferenceValue&&) noexcept = delete;
    ElevationReferenceValue operator=(const ecitygml::ElevationReferenceValue&) = delete;
    ElevationReferenceValue operator=(ecitygml::ElevationReferenceValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_ElevationReferenceValue_D_HPP
