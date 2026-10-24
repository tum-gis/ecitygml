#ifndef ecitygml_TrafficSpaceReferenceIterator_D_HPP
#define ecitygml_TrafficSpaceReferenceIterator_D_HPP

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
namespace capi { struct TrafficSpaceReference; }
class TrafficSpaceReference;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct TrafficSpaceReferenceIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of traffic space references, borrowed from a city model.
 */
class TrafficSpaceReferenceIterator {
public:

  inline const ecitygml::TrafficSpaceReference* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TrafficSpaceReferenceIterator* AsFFI() const;
    inline ecitygml::capi::TrafficSpaceReferenceIterator* AsFFI();
    inline static const ecitygml::TrafficSpaceReferenceIterator* FromFFI(const ecitygml::capi::TrafficSpaceReferenceIterator* ptr);
    inline static ecitygml::TrafficSpaceReferenceIterator* FromFFI(ecitygml::capi::TrafficSpaceReferenceIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    TrafficSpaceReferenceIterator() = delete;
    TrafficSpaceReferenceIterator(const ecitygml::TrafficSpaceReferenceIterator&) = delete;
    TrafficSpaceReferenceIterator(ecitygml::TrafficSpaceReferenceIterator&&) noexcept = delete;
    TrafficSpaceReferenceIterator operator=(const ecitygml::TrafficSpaceReferenceIterator&) = delete;
    TrafficSpaceReferenceIterator operator=(ecitygml::TrafficSpaceReferenceIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_TrafficSpaceReferenceIterator_D_HPP
