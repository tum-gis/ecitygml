#ifndef ECITYGML_CityFurnitureUsageValue_D_HPP
#define ECITYGML_CityFurnitureUsageValue_D_HPP

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
    struct CityFurnitureUsageValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `usage` property of a CityFurniture.
 */
class CityFurnitureUsageValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::CityFurnitureUsageValue* AsFFI() const;
    inline ecitygml::capi::CityFurnitureUsageValue* AsFFI();
    inline static const ecitygml::CityFurnitureUsageValue* FromFFI(const ecitygml::capi::CityFurnitureUsageValue* ptr);
    inline static ecitygml::CityFurnitureUsageValue* FromFFI(ecitygml::capi::CityFurnitureUsageValue* ptr);
    inline static void operator delete(void* ptr);
private:
    CityFurnitureUsageValue() = delete;
    CityFurnitureUsageValue(const ecitygml::CityFurnitureUsageValue&) = delete;
    CityFurnitureUsageValue(ecitygml::CityFurnitureUsageValue&&) noexcept = delete;
    CityFurnitureUsageValue operator=(const ecitygml::CityFurnitureUsageValue&) = delete;
    CityFurnitureUsageValue operator=(ecitygml::CityFurnitureUsageValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_CityFurnitureUsageValue_D_HPP
