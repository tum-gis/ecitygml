#ifndef ECITYGML_RoofTypeValue_D_HPP
#define ECITYGML_RoofTypeValue_D_HPP

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
namespace capi { struct Code; }
class Code;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct RoofTypeValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `roofType` property of a Building or BuildingPart.
 */
class RoofTypeValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::RoofTypeValue* AsFFI() const;
    inline ecitygml::capi::RoofTypeValue* AsFFI();
    inline static const ecitygml::RoofTypeValue* FromFFI(const ecitygml::capi::RoofTypeValue* ptr);
    inline static ecitygml::RoofTypeValue* FromFFI(ecitygml::capi::RoofTypeValue* ptr);
    inline static void operator delete(void* ptr);
private:
    RoofTypeValue() = delete;
    RoofTypeValue(const ecitygml::RoofTypeValue&) = delete;
    RoofTypeValue(ecitygml::RoofTypeValue&&) noexcept = delete;
    RoofTypeValue operator=(const ecitygml::RoofTypeValue&) = delete;
    RoofTypeValue operator=(ecitygml::RoofTypeValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_RoofTypeValue_D_HPP
