#ifndef ECITYGML_SectionPropertyIterator_D_HPP
#define ECITYGML_SectionPropertyIterator_D_HPP

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
namespace capi { struct SectionProperty; }
class SectionProperty;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct SectionPropertyIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over section properties, borrowed from a city model.
 */
class SectionPropertyIterator {
public:

  inline const ecitygml::SectionProperty* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::SectionPropertyIterator* AsFFI() const;
    inline ecitygml::capi::SectionPropertyIterator* AsFFI();
    inline static const ecitygml::SectionPropertyIterator* FromFFI(const ecitygml::capi::SectionPropertyIterator* ptr);
    inline static ecitygml::SectionPropertyIterator* FromFFI(ecitygml::capi::SectionPropertyIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    SectionPropertyIterator() = delete;
    SectionPropertyIterator(const ecitygml::SectionPropertyIterator&) = delete;
    SectionPropertyIterator(ecitygml::SectionPropertyIterator&&) noexcept = delete;
    SectionPropertyIterator operator=(const ecitygml::SectionPropertyIterator&) = delete;
    SectionPropertyIterator operator=(ecitygml::SectionPropertyIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_SectionPropertyIterator_D_HPP
