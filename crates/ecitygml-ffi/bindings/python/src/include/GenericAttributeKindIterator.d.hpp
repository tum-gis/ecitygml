#ifndef ECITYGML_GenericAttributeKindIterator_D_HPP
#define ECITYGML_GenericAttributeKindIterator_D_HPP

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
namespace capi { struct GenericAttributeKind; }
class GenericAttributeKind;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct GenericAttributeKindIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over generic attributes, borrowed from a city model.
 */
class GenericAttributeKindIterator {
public:

  inline const ecitygml::GenericAttributeKind* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::GenericAttributeKindIterator* AsFFI() const;
    inline ecitygml::capi::GenericAttributeKindIterator* AsFFI();
    inline static const ecitygml::GenericAttributeKindIterator* FromFFI(const ecitygml::capi::GenericAttributeKindIterator* ptr);
    inline static ecitygml::GenericAttributeKindIterator* FromFFI(ecitygml::capi::GenericAttributeKindIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    GenericAttributeKindIterator() = delete;
    GenericAttributeKindIterator(const ecitygml::GenericAttributeKindIterator&) = delete;
    GenericAttributeKindIterator(ecitygml::GenericAttributeKindIterator&&) noexcept = delete;
    GenericAttributeKindIterator operator=(const ecitygml::GenericAttributeKindIterator&) = delete;
    GenericAttributeKindIterator operator=(ecitygml::GenericAttributeKindIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_GenericAttributeKindIterator_D_HPP
