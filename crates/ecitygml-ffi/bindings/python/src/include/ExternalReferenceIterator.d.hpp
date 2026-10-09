#ifndef ECITYGML_ExternalReferenceIterator_D_HPP
#define ECITYGML_ExternalReferenceIterator_D_HPP

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
namespace capi { struct ExternalReference; }
class ExternalReference;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct ExternalReferenceIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over external references, borrowed from a city model.
 */
class ExternalReferenceIterator {
public:

  inline const ecitygml::ExternalReference* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::ExternalReferenceIterator* AsFFI() const;
    inline ecitygml::capi::ExternalReferenceIterator* AsFFI();
    inline static const ecitygml::ExternalReferenceIterator* FromFFI(const ecitygml::capi::ExternalReferenceIterator* ptr);
    inline static ecitygml::ExternalReferenceIterator* FromFFI(ecitygml::capi::ExternalReferenceIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    ExternalReferenceIterator() = delete;
    ExternalReferenceIterator(const ecitygml::ExternalReferenceIterator&) = delete;
    ExternalReferenceIterator(ecitygml::ExternalReferenceIterator&&) noexcept = delete;
    ExternalReferenceIterator operator=(const ecitygml::ExternalReferenceIterator&) = delete;
    ExternalReferenceIterator operator=(ecitygml::ExternalReferenceIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_ExternalReferenceIterator_D_HPP
