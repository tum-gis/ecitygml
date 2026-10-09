#ifndef ECITYGML_Occupancy_D_HPP
#define ECITYGML_Occupancy_D_HPP

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
namespace capi { struct IntervalValue; }
class IntervalValue;
namespace capi { struct OccupantTypeValue; }
class OccupantTypeValue;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct Occupancy;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The number of occupants of a feature, borrowed from a city model.
 */
class Occupancy {
public:

  inline int64_t number_of_occupants() const;

  inline const ecitygml::IntervalValue* interval() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::OccupantTypeValue* occupant_type() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::Occupancy* AsFFI() const;
    inline ecitygml::capi::Occupancy* AsFFI();
    inline static const ecitygml::Occupancy* FromFFI(const ecitygml::capi::Occupancy* ptr);
    inline static ecitygml::Occupancy* FromFFI(ecitygml::capi::Occupancy* ptr);
    inline static void operator delete(void* ptr);
private:
    Occupancy() = delete;
    Occupancy(const ecitygml::Occupancy&) = delete;
    Occupancy(ecitygml::Occupancy&&) noexcept = delete;
    Occupancy operator=(const ecitygml::Occupancy&) = delete;
    Occupancy operator=(ecitygml::Occupancy&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_Occupancy_D_HPP
