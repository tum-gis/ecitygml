#ifndef ECITYGML_AbstractSurfacePatchKindIterator_D_HPP
#define ECITYGML_AbstractSurfacePatchKindIterator_D_HPP

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
namespace capi { struct AbstractSurfacePatchKind; }
class AbstractSurfacePatchKind;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct AbstractSurfacePatchKindIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over surface patches, borrowed from a city model.
 */
class AbstractSurfacePatchKindIterator {
public:

  inline const ecitygml::AbstractSurfacePatchKind* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AbstractSurfacePatchKindIterator* AsFFI() const;
    inline ecitygml::capi::AbstractSurfacePatchKindIterator* AsFFI();
    inline static const ecitygml::AbstractSurfacePatchKindIterator* FromFFI(const ecitygml::capi::AbstractSurfacePatchKindIterator* ptr);
    inline static ecitygml::AbstractSurfacePatchKindIterator* FromFFI(ecitygml::capi::AbstractSurfacePatchKindIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractSurfacePatchKindIterator() = delete;
    AbstractSurfacePatchKindIterator(const ecitygml::AbstractSurfacePatchKindIterator&) = delete;
    AbstractSurfacePatchKindIterator(ecitygml::AbstractSurfacePatchKindIterator&&) noexcept = delete;
    AbstractSurfacePatchKindIterator operator=(const ecitygml::AbstractSurfacePatchKindIterator&) = delete;
    AbstractSurfacePatchKindIterator operator=(ecitygml::AbstractSurfacePatchKindIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AbstractSurfacePatchKindIterator_D_HPP
