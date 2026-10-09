#ifndef ECITYGML_OccupancyIterator_D_HPP
#define ECITYGML_OccupancyIterator_D_HPP

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
namespace capi { struct Occupancy; }
class Occupancy;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct OccupancyIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of occupancies, borrowed from a city model.
 */
class OccupancyIterator {
public:

  inline const ecitygml::Occupancy* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::OccupancyIterator* AsFFI() const;
    inline ecitygml::capi::OccupancyIterator* AsFFI();
    inline static const ecitygml::OccupancyIterator* FromFFI(const ecitygml::capi::OccupancyIterator* ptr);
    inline static ecitygml::OccupancyIterator* FromFFI(ecitygml::capi::OccupancyIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    OccupancyIterator() = delete;
    OccupancyIterator(const ecitygml::OccupancyIterator&) = delete;
    OccupancyIterator(ecitygml::OccupancyIterator&&) noexcept = delete;
    OccupancyIterator operator=(const ecitygml::OccupancyIterator&) = delete;
    OccupancyIterator operator=(ecitygml::OccupancyIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_OccupancyIterator_D_HPP
