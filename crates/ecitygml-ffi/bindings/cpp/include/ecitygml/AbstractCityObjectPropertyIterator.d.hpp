#ifndef ecitygml_AbstractCityObjectPropertyIterator_D_HPP
#define ecitygml_AbstractCityObjectPropertyIterator_D_HPP

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
namespace capi { struct AbstractCityObjectProperty; }
class AbstractCityObjectProperty;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct AbstractCityObjectPropertyIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over city object properties, borrowed from a city model.
 */
class AbstractCityObjectPropertyIterator {
public:

  inline const ecitygml::AbstractCityObjectProperty* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AbstractCityObjectPropertyIterator* AsFFI() const;
    inline ecitygml::capi::AbstractCityObjectPropertyIterator* AsFFI();
    inline static const ecitygml::AbstractCityObjectPropertyIterator* FromFFI(const ecitygml::capi::AbstractCityObjectPropertyIterator* ptr);
    inline static ecitygml::AbstractCityObjectPropertyIterator* FromFFI(ecitygml::capi::AbstractCityObjectPropertyIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractCityObjectPropertyIterator() = delete;
    AbstractCityObjectPropertyIterator(const ecitygml::AbstractCityObjectPropertyIterator&) = delete;
    AbstractCityObjectPropertyIterator(ecitygml::AbstractCityObjectPropertyIterator&&) noexcept = delete;
    AbstractCityObjectPropertyIterator operator=(const ecitygml::AbstractCityObjectPropertyIterator&) = delete;
    AbstractCityObjectPropertyIterator operator=(ecitygml::AbstractCityObjectPropertyIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_AbstractCityObjectPropertyIterator_D_HPP
