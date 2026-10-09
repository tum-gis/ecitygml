#ifndef ECITYGML_SolitaryVegetationObjectClassValue_D_HPP
#define ECITYGML_SolitaryVegetationObjectClassValue_D_HPP

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
    struct SolitaryVegetationObjectClassValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `class` property of a SolitaryVegetationObject.
 */
class SolitaryVegetationObjectClassValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::SolitaryVegetationObjectClassValue* AsFFI() const;
    inline ecitygml::capi::SolitaryVegetationObjectClassValue* AsFFI();
    inline static const ecitygml::SolitaryVegetationObjectClassValue* FromFFI(const ecitygml::capi::SolitaryVegetationObjectClassValue* ptr);
    inline static ecitygml::SolitaryVegetationObjectClassValue* FromFFI(ecitygml::capi::SolitaryVegetationObjectClassValue* ptr);
    inline static void operator delete(void* ptr);
private:
    SolitaryVegetationObjectClassValue() = delete;
    SolitaryVegetationObjectClassValue(const ecitygml::SolitaryVegetationObjectClassValue&) = delete;
    SolitaryVegetationObjectClassValue(ecitygml::SolitaryVegetationObjectClassValue&&) noexcept = delete;
    SolitaryVegetationObjectClassValue operator=(const ecitygml::SolitaryVegetationObjectClassValue&) = delete;
    SolitaryVegetationObjectClassValue operator=(ecitygml::SolitaryVegetationObjectClassValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_SolitaryVegetationObjectClassValue_D_HPP
