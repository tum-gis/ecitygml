#ifndef ecitygml_RoadFunctionValueIterator_D_HPP
#define ecitygml_RoadFunctionValueIterator_D_HPP

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
namespace capi { struct RoadFunctionValue; }
class RoadFunctionValue;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct RoadFunctionValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class RoadFunctionValueIterator {
public:

  inline const ecitygml::RoadFunctionValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::RoadFunctionValueIterator* AsFFI() const;
    inline ecitygml::capi::RoadFunctionValueIterator* AsFFI();
    inline static const ecitygml::RoadFunctionValueIterator* FromFFI(const ecitygml::capi::RoadFunctionValueIterator* ptr);
    inline static ecitygml::RoadFunctionValueIterator* FromFFI(ecitygml::capi::RoadFunctionValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    RoadFunctionValueIterator() = delete;
    RoadFunctionValueIterator(const ecitygml::RoadFunctionValueIterator&) = delete;
    RoadFunctionValueIterator(ecitygml::RoadFunctionValueIterator&&) noexcept = delete;
    RoadFunctionValueIterator operator=(const ecitygml::RoadFunctionValueIterator&) = delete;
    RoadFunctionValueIterator operator=(ecitygml::RoadFunctionValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_RoadFunctionValueIterator_D_HPP
