#ifndef ecitygml_CityFurnitureFunctionValue_D_HPP
#define ecitygml_CityFurnitureFunctionValue_D_HPP

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
    struct CityFurnitureFunctionValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `function` property of a CityFurniture.
 */
class CityFurnitureFunctionValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::CityFurnitureFunctionValue* AsFFI() const;
    inline ecitygml::capi::CityFurnitureFunctionValue* AsFFI();
    inline static const ecitygml::CityFurnitureFunctionValue* FromFFI(const ecitygml::capi::CityFurnitureFunctionValue* ptr);
    inline static ecitygml::CityFurnitureFunctionValue* FromFFI(ecitygml::capi::CityFurnitureFunctionValue* ptr);
    inline static void operator delete(void* ptr);
private:
    CityFurnitureFunctionValue() = delete;
    CityFurnitureFunctionValue(const ecitygml::CityFurnitureFunctionValue&) = delete;
    CityFurnitureFunctionValue(ecitygml::CityFurnitureFunctionValue&&) noexcept = delete;
    CityFurnitureFunctionValue operator=(const ecitygml::CityFurnitureFunctionValue&) = delete;
    CityFurnitureFunctionValue operator=(ecitygml::CityFurnitureFunctionValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_CityFurnitureFunctionValue_D_HPP
