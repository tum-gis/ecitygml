#ifndef ECITYGML_TrafficSpaceFunctionValueIterator_D_HPP
#define ECITYGML_TrafficSpaceFunctionValueIterator_D_HPP

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
namespace capi { struct TrafficSpaceFunctionValue; }
class TrafficSpaceFunctionValue;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct TrafficSpaceFunctionValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class TrafficSpaceFunctionValueIterator {
public:

  inline const ecitygml::TrafficSpaceFunctionValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TrafficSpaceFunctionValueIterator* AsFFI() const;
    inline ecitygml::capi::TrafficSpaceFunctionValueIterator* AsFFI();
    inline static const ecitygml::TrafficSpaceFunctionValueIterator* FromFFI(const ecitygml::capi::TrafficSpaceFunctionValueIterator* ptr);
    inline static ecitygml::TrafficSpaceFunctionValueIterator* FromFFI(ecitygml::capi::TrafficSpaceFunctionValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    TrafficSpaceFunctionValueIterator() = delete;
    TrafficSpaceFunctionValueIterator(const ecitygml::TrafficSpaceFunctionValueIterator&) = delete;
    TrafficSpaceFunctionValueIterator(ecitygml::TrafficSpaceFunctionValueIterator&&) noexcept = delete;
    TrafficSpaceFunctionValueIterator operator=(const ecitygml::TrafficSpaceFunctionValueIterator&) = delete;
    TrafficSpaceFunctionValueIterator operator=(ecitygml::TrafficSpaceFunctionValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_TrafficSpaceFunctionValueIterator_D_HPP
