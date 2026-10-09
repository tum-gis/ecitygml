#ifndef ECITYGML_HolePropertyIterator_D_HPP
#define ECITYGML_HolePropertyIterator_D_HPP

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
namespace capi { struct HoleProperty; }
class HoleProperty;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct HolePropertyIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over hole properties, borrowed from a city model.
 */
class HolePropertyIterator {
public:

  inline const ecitygml::HoleProperty* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::HolePropertyIterator* AsFFI() const;
    inline ecitygml::capi::HolePropertyIterator* AsFFI();
    inline static const ecitygml::HolePropertyIterator* FromFFI(const ecitygml::capi::HolePropertyIterator* ptr);
    inline static ecitygml::HolePropertyIterator* FromFFI(ecitygml::capi::HolePropertyIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    HolePropertyIterator() = delete;
    HolePropertyIterator(const ecitygml::HolePropertyIterator&) = delete;
    HolePropertyIterator(ecitygml::HolePropertyIterator&&) noexcept = delete;
    HolePropertyIterator operator=(const ecitygml::HolePropertyIterator&) = delete;
    HolePropertyIterator operator=(ecitygml::HolePropertyIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_HolePropertyIterator_D_HPP
