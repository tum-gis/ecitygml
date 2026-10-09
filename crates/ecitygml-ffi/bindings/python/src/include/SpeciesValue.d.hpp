#ifndef ECITYGML_SpeciesValue_D_HPP
#define ECITYGML_SpeciesValue_D_HPP

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
    struct SpeciesValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `species` property of a SolitaryVegetationObject.
 */
class SpeciesValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::SpeciesValue* AsFFI() const;
    inline ecitygml::capi::SpeciesValue* AsFFI();
    inline static const ecitygml::SpeciesValue* FromFFI(const ecitygml::capi::SpeciesValue* ptr);
    inline static ecitygml::SpeciesValue* FromFFI(ecitygml::capi::SpeciesValue* ptr);
    inline static void operator delete(void* ptr);
private:
    SpeciesValue() = delete;
    SpeciesValue(const ecitygml::SpeciesValue&) = delete;
    SpeciesValue(ecitygml::SpeciesValue&&) noexcept = delete;
    SpeciesValue operator=(const ecitygml::SpeciesValue&) = delete;
    SpeciesValue operator=(ecitygml::SpeciesValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_SpeciesValue_D_HPP
