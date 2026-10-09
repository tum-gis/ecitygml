#ifndef ecitygml_TunnelFunctionValueIterator_D_HPP
#define ecitygml_TunnelFunctionValueIterator_D_HPP

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
namespace capi { struct TunnelFunctionValue; }
class TunnelFunctionValue;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct TunnelFunctionValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class TunnelFunctionValueIterator {
public:

  inline const ecitygml::TunnelFunctionValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TunnelFunctionValueIterator* AsFFI() const;
    inline ecitygml::capi::TunnelFunctionValueIterator* AsFFI();
    inline static const ecitygml::TunnelFunctionValueIterator* FromFFI(const ecitygml::capi::TunnelFunctionValueIterator* ptr);
    inline static ecitygml::TunnelFunctionValueIterator* FromFFI(ecitygml::capi::TunnelFunctionValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    TunnelFunctionValueIterator() = delete;
    TunnelFunctionValueIterator(const ecitygml::TunnelFunctionValueIterator&) = delete;
    TunnelFunctionValueIterator(ecitygml::TunnelFunctionValueIterator&&) noexcept = delete;
    TunnelFunctionValueIterator operator=(const ecitygml::TunnelFunctionValueIterator&) = delete;
    TunnelFunctionValueIterator operator=(ecitygml::TunnelFunctionValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_TunnelFunctionValueIterator_D_HPP
