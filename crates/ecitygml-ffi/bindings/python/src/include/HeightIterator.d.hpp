#ifndef ECITYGML_HeightIterator_D_HPP
#define ECITYGML_HeightIterator_D_HPP

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
namespace capi { struct Height; }
class Height;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct HeightIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over heights, borrowed from a city model.
 */
class HeightIterator {
public:

  inline const ecitygml::Height* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::HeightIterator* AsFFI() const;
    inline ecitygml::capi::HeightIterator* AsFFI();
    inline static const ecitygml::HeightIterator* FromFFI(const ecitygml::capi::HeightIterator* ptr);
    inline static ecitygml::HeightIterator* FromFFI(ecitygml::capi::HeightIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    HeightIterator() = delete;
    HeightIterator(const ecitygml::HeightIterator&) = delete;
    HeightIterator(ecitygml::HeightIterator&&) noexcept = delete;
    HeightIterator operator=(const ecitygml::HeightIterator&) = delete;
    HeightIterator operator=(ecitygml::HeightIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_HeightIterator_D_HPP
