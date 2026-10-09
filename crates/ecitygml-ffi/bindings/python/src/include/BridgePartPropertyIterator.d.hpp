#ifndef ECITYGML_BridgePartPropertyIterator_D_HPP
#define ECITYGML_BridgePartPropertyIterator_D_HPP

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
namespace capi { struct BridgePartProperty; }
class BridgePartProperty;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct BridgePartPropertyIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over bridge part properties, borrowed from a city model.
 */
class BridgePartPropertyIterator {
public:

  inline const ecitygml::BridgePartProperty* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::BridgePartPropertyIterator* AsFFI() const;
    inline ecitygml::capi::BridgePartPropertyIterator* AsFFI();
    inline static const ecitygml::BridgePartPropertyIterator* FromFFI(const ecitygml::capi::BridgePartPropertyIterator* ptr);
    inline static ecitygml::BridgePartPropertyIterator* FromFFI(ecitygml::capi::BridgePartPropertyIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    BridgePartPropertyIterator() = delete;
    BridgePartPropertyIterator(const ecitygml::BridgePartPropertyIterator&) = delete;
    BridgePartPropertyIterator(ecitygml::BridgePartPropertyIterator&&) noexcept = delete;
    BridgePartPropertyIterator operator=(const ecitygml::BridgePartPropertyIterator&) = delete;
    BridgePartPropertyIterator operator=(ecitygml::BridgePartPropertyIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_BridgePartPropertyIterator_D_HPP
