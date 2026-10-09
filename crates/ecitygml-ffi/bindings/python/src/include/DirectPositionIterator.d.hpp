#ifndef ECITYGML_DirectPositionIterator_D_HPP
#define ECITYGML_DirectPositionIterator_D_HPP

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
namespace capi { struct DirectPosition; }
class DirectPosition;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct DirectPositionIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over positions, borrowed from a city model.
 */
class DirectPositionIterator {
public:

  inline const ecitygml::DirectPosition* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::DirectPositionIterator* AsFFI() const;
    inline ecitygml::capi::DirectPositionIterator* AsFFI();
    inline static const ecitygml::DirectPositionIterator* FromFFI(const ecitygml::capi::DirectPositionIterator* ptr);
    inline static ecitygml::DirectPositionIterator* FromFFI(ecitygml::capi::DirectPositionIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    DirectPositionIterator() = delete;
    DirectPositionIterator(const ecitygml::DirectPositionIterator&) = delete;
    DirectPositionIterator(ecitygml::DirectPositionIterator&&) noexcept = delete;
    DirectPositionIterator operator=(const ecitygml::DirectPositionIterator&) = delete;
    DirectPositionIterator operator=(ecitygml::DirectPositionIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_DirectPositionIterator_D_HPP
