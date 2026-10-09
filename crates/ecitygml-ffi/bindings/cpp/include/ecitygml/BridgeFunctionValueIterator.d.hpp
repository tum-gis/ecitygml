#ifndef ecitygml_BridgeFunctionValueIterator_D_HPP
#define ecitygml_BridgeFunctionValueIterator_D_HPP

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
namespace capi { struct BridgeFunctionValue; }
class BridgeFunctionValue;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct BridgeFunctionValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class BridgeFunctionValueIterator {
public:

  inline const ecitygml::BridgeFunctionValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::BridgeFunctionValueIterator* AsFFI() const;
    inline ecitygml::capi::BridgeFunctionValueIterator* AsFFI();
    inline static const ecitygml::BridgeFunctionValueIterator* FromFFI(const ecitygml::capi::BridgeFunctionValueIterator* ptr);
    inline static ecitygml::BridgeFunctionValueIterator* FromFFI(ecitygml::capi::BridgeFunctionValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    BridgeFunctionValueIterator() = delete;
    BridgeFunctionValueIterator(const ecitygml::BridgeFunctionValueIterator&) = delete;
    BridgeFunctionValueIterator(ecitygml::BridgeFunctionValueIterator&&) noexcept = delete;
    BridgeFunctionValueIterator operator=(const ecitygml::BridgeFunctionValueIterator&) = delete;
    BridgeFunctionValueIterator operator=(ecitygml::BridgeFunctionValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_BridgeFunctionValueIterator_D_HPP
