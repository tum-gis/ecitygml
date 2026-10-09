#ifndef ECITYGML_TunnelPartPropertyIterator_D_HPP
#define ECITYGML_TunnelPartPropertyIterator_D_HPP

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
namespace capi { struct TunnelPartProperty; }
class TunnelPartProperty;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct TunnelPartPropertyIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over tunnel part properties, borrowed from a city model.
 */
class TunnelPartPropertyIterator {
public:

  inline const ecitygml::TunnelPartProperty* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TunnelPartPropertyIterator* AsFFI() const;
    inline ecitygml::capi::TunnelPartPropertyIterator* AsFFI();
    inline static const ecitygml::TunnelPartPropertyIterator* FromFFI(const ecitygml::capi::TunnelPartPropertyIterator* ptr);
    inline static ecitygml::TunnelPartPropertyIterator* FromFFI(ecitygml::capi::TunnelPartPropertyIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    TunnelPartPropertyIterator() = delete;
    TunnelPartPropertyIterator(const ecitygml::TunnelPartPropertyIterator&) = delete;
    TunnelPartPropertyIterator(ecitygml::TunnelPartPropertyIterator&&) noexcept = delete;
    TunnelPartPropertyIterator operator=(const ecitygml::TunnelPartPropertyIterator&) = delete;
    TunnelPartPropertyIterator operator=(ecitygml::TunnelPartPropertyIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_TunnelPartPropertyIterator_D_HPP
