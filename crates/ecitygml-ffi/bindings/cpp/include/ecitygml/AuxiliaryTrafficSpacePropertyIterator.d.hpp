#ifndef ecitygml_AuxiliaryTrafficSpacePropertyIterator_D_HPP
#define ecitygml_AuxiliaryTrafficSpacePropertyIterator_D_HPP

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
namespace capi { struct AuxiliaryTrafficSpaceProperty; }
class AuxiliaryTrafficSpaceProperty;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct AuxiliaryTrafficSpacePropertyIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over auxiliary traffic space properties, borrowed from a city model.
 */
class AuxiliaryTrafficSpacePropertyIterator {
public:

  inline const ecitygml::AuxiliaryTrafficSpaceProperty* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AuxiliaryTrafficSpacePropertyIterator* AsFFI() const;
    inline ecitygml::capi::AuxiliaryTrafficSpacePropertyIterator* AsFFI();
    inline static const ecitygml::AuxiliaryTrafficSpacePropertyIterator* FromFFI(const ecitygml::capi::AuxiliaryTrafficSpacePropertyIterator* ptr);
    inline static ecitygml::AuxiliaryTrafficSpacePropertyIterator* FromFFI(ecitygml::capi::AuxiliaryTrafficSpacePropertyIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    AuxiliaryTrafficSpacePropertyIterator() = delete;
    AuxiliaryTrafficSpacePropertyIterator(const ecitygml::AuxiliaryTrafficSpacePropertyIterator&) = delete;
    AuxiliaryTrafficSpacePropertyIterator(ecitygml::AuxiliaryTrafficSpacePropertyIterator&&) noexcept = delete;
    AuxiliaryTrafficSpacePropertyIterator operator=(const ecitygml::AuxiliaryTrafficSpacePropertyIterator&) = delete;
    AuxiliaryTrafficSpacePropertyIterator operator=(ecitygml::AuxiliaryTrafficSpacePropertyIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_AuxiliaryTrafficSpacePropertyIterator_D_HPP
