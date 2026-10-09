#ifndef ecitygml_AbstractRingKindIterator_D_HPP
#define ecitygml_AbstractRingKindIterator_D_HPP

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
namespace capi { struct AbstractRingKind; }
class AbstractRingKind;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct AbstractRingKindIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over rings (e.g. a polygon's interior rings), borrowed from a city model.
 */
class AbstractRingKindIterator {
public:

  inline const ecitygml::AbstractRingKind* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AbstractRingKindIterator* AsFFI() const;
    inline ecitygml::capi::AbstractRingKindIterator* AsFFI();
    inline static const ecitygml::AbstractRingKindIterator* FromFFI(const ecitygml::capi::AbstractRingKindIterator* ptr);
    inline static ecitygml::AbstractRingKindIterator* FromFFI(ecitygml::capi::AbstractRingKindIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractRingKindIterator() = delete;
    AbstractRingKindIterator(const ecitygml::AbstractRingKindIterator&) = delete;
    AbstractRingKindIterator(ecitygml::AbstractRingKindIterator&&) noexcept = delete;
    AbstractRingKindIterator operator=(const ecitygml::AbstractRingKindIterator&) = delete;
    AbstractRingKindIterator operator=(ecitygml::AbstractRingKindIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_AbstractRingKindIterator_D_HPP
