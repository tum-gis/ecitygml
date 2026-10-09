#ifndef ECITYGML_AbstractCurvePropertyIterator_D_HPP
#define ECITYGML_AbstractCurvePropertyIterator_D_HPP

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
namespace capi { struct AbstractCurveProperty; }
class AbstractCurveProperty;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct AbstractCurvePropertyIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over curve properties, borrowed from a city model.
 */
class AbstractCurvePropertyIterator {
public:

  inline const ecitygml::AbstractCurveProperty* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AbstractCurvePropertyIterator* AsFFI() const;
    inline ecitygml::capi::AbstractCurvePropertyIterator* AsFFI();
    inline static const ecitygml::AbstractCurvePropertyIterator* FromFFI(const ecitygml::capi::AbstractCurvePropertyIterator* ptr);
    inline static ecitygml::AbstractCurvePropertyIterator* FromFFI(ecitygml::capi::AbstractCurvePropertyIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractCurvePropertyIterator() = delete;
    AbstractCurvePropertyIterator(const ecitygml::AbstractCurvePropertyIterator&) = delete;
    AbstractCurvePropertyIterator(ecitygml::AbstractCurvePropertyIterator&&) noexcept = delete;
    AbstractCurvePropertyIterator operator=(const ecitygml::AbstractCurvePropertyIterator&) = delete;
    AbstractCurvePropertyIterator operator=(ecitygml::AbstractCurvePropertyIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AbstractCurvePropertyIterator_D_HPP
