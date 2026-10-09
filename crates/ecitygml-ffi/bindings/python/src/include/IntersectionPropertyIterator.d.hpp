#ifndef ECITYGML_IntersectionPropertyIterator_D_HPP
#define ECITYGML_IntersectionPropertyIterator_D_HPP

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
namespace capi { struct IntersectionProperty; }
class IntersectionProperty;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct IntersectionPropertyIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over intersection properties, borrowed from a city model.
 */
class IntersectionPropertyIterator {
public:

  inline const ecitygml::IntersectionProperty* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::IntersectionPropertyIterator* AsFFI() const;
    inline ecitygml::capi::IntersectionPropertyIterator* AsFFI();
    inline static const ecitygml::IntersectionPropertyIterator* FromFFI(const ecitygml::capi::IntersectionPropertyIterator* ptr);
    inline static ecitygml::IntersectionPropertyIterator* FromFFI(ecitygml::capi::IntersectionPropertyIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    IntersectionPropertyIterator() = delete;
    IntersectionPropertyIterator(const ecitygml::IntersectionPropertyIterator&) = delete;
    IntersectionPropertyIterator(ecitygml::IntersectionPropertyIterator&&) noexcept = delete;
    IntersectionPropertyIterator operator=(const ecitygml::IntersectionPropertyIterator&) = delete;
    IntersectionPropertyIterator operator=(ecitygml::IntersectionPropertyIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_IntersectionPropertyIterator_D_HPP
