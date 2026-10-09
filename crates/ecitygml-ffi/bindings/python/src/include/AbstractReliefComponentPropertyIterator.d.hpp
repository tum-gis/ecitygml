#ifndef ECITYGML_AbstractReliefComponentPropertyIterator_D_HPP
#define ECITYGML_AbstractReliefComponentPropertyIterator_D_HPP

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
namespace capi { struct AbstractReliefComponentProperty; }
class AbstractReliefComponentProperty;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct AbstractReliefComponentPropertyIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over relief component properties, borrowed from a city model.
 */
class AbstractReliefComponentPropertyIterator {
public:

  inline const ecitygml::AbstractReliefComponentProperty* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AbstractReliefComponentPropertyIterator* AsFFI() const;
    inline ecitygml::capi::AbstractReliefComponentPropertyIterator* AsFFI();
    inline static const ecitygml::AbstractReliefComponentPropertyIterator* FromFFI(const ecitygml::capi::AbstractReliefComponentPropertyIterator* ptr);
    inline static ecitygml::AbstractReliefComponentPropertyIterator* FromFFI(ecitygml::capi::AbstractReliefComponentPropertyIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractReliefComponentPropertyIterator() = delete;
    AbstractReliefComponentPropertyIterator(const ecitygml::AbstractReliefComponentPropertyIterator&) = delete;
    AbstractReliefComponentPropertyIterator(ecitygml::AbstractReliefComponentPropertyIterator&&) noexcept = delete;
    AbstractReliefComponentPropertyIterator operator=(const ecitygml::AbstractReliefComponentPropertyIterator&) = delete;
    AbstractReliefComponentPropertyIterator operator=(ecitygml::AbstractReliefComponentPropertyIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AbstractReliefComponentPropertyIterator_D_HPP
