#ifndef ECITYGML_TrafficSpacePropertyIterator_D_HPP
#define ECITYGML_TrafficSpacePropertyIterator_D_HPP

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
namespace capi { struct TrafficSpaceProperty; }
class TrafficSpaceProperty;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct TrafficSpacePropertyIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over traffic space properties, borrowed from a city model.
 */
class TrafficSpacePropertyIterator {
public:

  inline const ecitygml::TrafficSpaceProperty* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TrafficSpacePropertyIterator* AsFFI() const;
    inline ecitygml::capi::TrafficSpacePropertyIterator* AsFFI();
    inline static const ecitygml::TrafficSpacePropertyIterator* FromFFI(const ecitygml::capi::TrafficSpacePropertyIterator* ptr);
    inline static ecitygml::TrafficSpacePropertyIterator* FromFFI(ecitygml::capi::TrafficSpacePropertyIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    TrafficSpacePropertyIterator() = delete;
    TrafficSpacePropertyIterator(const ecitygml::TrafficSpacePropertyIterator&) = delete;
    TrafficSpacePropertyIterator(ecitygml::TrafficSpacePropertyIterator&&) noexcept = delete;
    TrafficSpacePropertyIterator operator=(const ecitygml::TrafficSpacePropertyIterator&) = delete;
    TrafficSpacePropertyIterator operator=(ecitygml::TrafficSpacePropertyIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_TrafficSpacePropertyIterator_D_HPP
