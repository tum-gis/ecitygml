#ifndef ECITYGML_MarkingPropertyIterator_D_HPP
#define ECITYGML_MarkingPropertyIterator_D_HPP

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
namespace capi { struct MarkingProperty; }
class MarkingProperty;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct MarkingPropertyIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over marking properties, borrowed from a city model.
 */
class MarkingPropertyIterator {
public:

  inline const ecitygml::MarkingProperty* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::MarkingPropertyIterator* AsFFI() const;
    inline ecitygml::capi::MarkingPropertyIterator* AsFFI();
    inline static const ecitygml::MarkingPropertyIterator* FromFFI(const ecitygml::capi::MarkingPropertyIterator* ptr);
    inline static ecitygml::MarkingPropertyIterator* FromFFI(ecitygml::capi::MarkingPropertyIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    MarkingPropertyIterator() = delete;
    MarkingPropertyIterator(const ecitygml::MarkingPropertyIterator&) = delete;
    MarkingPropertyIterator(ecitygml::MarkingPropertyIterator&&) noexcept = delete;
    MarkingPropertyIterator operator=(const ecitygml::MarkingPropertyIterator&) = delete;
    MarkingPropertyIterator operator=(ecitygml::MarkingPropertyIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_MarkingPropertyIterator_D_HPP
