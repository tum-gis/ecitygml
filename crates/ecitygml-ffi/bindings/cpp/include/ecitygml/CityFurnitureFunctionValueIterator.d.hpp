#ifndef ecitygml_CityFurnitureFunctionValueIterator_D_HPP
#define ecitygml_CityFurnitureFunctionValueIterator_D_HPP

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
namespace capi { struct CityFurnitureFunctionValue; }
class CityFurnitureFunctionValue;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct CityFurnitureFunctionValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class CityFurnitureFunctionValueIterator {
public:

  inline const ecitygml::CityFurnitureFunctionValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::CityFurnitureFunctionValueIterator* AsFFI() const;
    inline ecitygml::capi::CityFurnitureFunctionValueIterator* AsFFI();
    inline static const ecitygml::CityFurnitureFunctionValueIterator* FromFFI(const ecitygml::capi::CityFurnitureFunctionValueIterator* ptr);
    inline static ecitygml::CityFurnitureFunctionValueIterator* FromFFI(ecitygml::capi::CityFurnitureFunctionValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    CityFurnitureFunctionValueIterator() = delete;
    CityFurnitureFunctionValueIterator(const ecitygml::CityFurnitureFunctionValueIterator&) = delete;
    CityFurnitureFunctionValueIterator(ecitygml::CityFurnitureFunctionValueIterator&&) noexcept = delete;
    CityFurnitureFunctionValueIterator operator=(const ecitygml::CityFurnitureFunctionValueIterator&) = delete;
    CityFurnitureFunctionValueIterator operator=(ecitygml::CityFurnitureFunctionValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_CityFurnitureFunctionValueIterator_D_HPP
