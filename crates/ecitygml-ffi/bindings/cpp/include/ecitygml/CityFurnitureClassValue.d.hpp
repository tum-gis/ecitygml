#ifndef ecitygml_CityFurnitureClassValue_D_HPP
#define ecitygml_CityFurnitureClassValue_D_HPP

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
    struct CityFurnitureClassValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `class` property of a CityFurniture.
 */
class CityFurnitureClassValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::CityFurnitureClassValue* AsFFI() const;
    inline ecitygml::capi::CityFurnitureClassValue* AsFFI();
    inline static const ecitygml::CityFurnitureClassValue* FromFFI(const ecitygml::capi::CityFurnitureClassValue* ptr);
    inline static ecitygml::CityFurnitureClassValue* FromFFI(ecitygml::capi::CityFurnitureClassValue* ptr);
    inline static void operator delete(void* ptr);
private:
    CityFurnitureClassValue() = delete;
    CityFurnitureClassValue(const ecitygml::CityFurnitureClassValue&) = delete;
    CityFurnitureClassValue(ecitygml::CityFurnitureClassValue&&) noexcept = delete;
    CityFurnitureClassValue operator=(const ecitygml::CityFurnitureClassValue&) = delete;
    CityFurnitureClassValue operator=(ecitygml::CityFurnitureClassValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_CityFurnitureClassValue_D_HPP
