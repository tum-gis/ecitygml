#ifndef ecitygml_TrafficAreaFunctionValueIterator_D_HPP
#define ecitygml_TrafficAreaFunctionValueIterator_D_HPP

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
namespace capi { struct TrafficAreaFunctionValue; }
class TrafficAreaFunctionValue;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct TrafficAreaFunctionValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class TrafficAreaFunctionValueIterator {
public:

  inline const ecitygml::TrafficAreaFunctionValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TrafficAreaFunctionValueIterator* AsFFI() const;
    inline ecitygml::capi::TrafficAreaFunctionValueIterator* AsFFI();
    inline static const ecitygml::TrafficAreaFunctionValueIterator* FromFFI(const ecitygml::capi::TrafficAreaFunctionValueIterator* ptr);
    inline static ecitygml::TrafficAreaFunctionValueIterator* FromFFI(ecitygml::capi::TrafficAreaFunctionValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    TrafficAreaFunctionValueIterator() = delete;
    TrafficAreaFunctionValueIterator(const ecitygml::TrafficAreaFunctionValueIterator&) = delete;
    TrafficAreaFunctionValueIterator(ecitygml::TrafficAreaFunctionValueIterator&&) noexcept = delete;
    TrafficAreaFunctionValueIterator operator=(const ecitygml::TrafficAreaFunctionValueIterator&) = delete;
    TrafficAreaFunctionValueIterator operator=(ecitygml::TrafficAreaFunctionValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_TrafficAreaFunctionValueIterator_D_HPP
