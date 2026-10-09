#ifndef ECITYGML_AbstractCityObjectKindRef_D_HPP
#define ECITYGML_AbstractCityObjectKindRef_D_HPP

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
class FeatureType;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct AbstractCityObjectKindRef;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A reference to a city object of any type; convert it with
 * `AbstractFeatureKindRef::from_city_object` and then e.g. `Building::try_from`.
 */
class AbstractCityObjectKindRef {
public:

  inline ecitygml::FeatureType feature_type() const;

    inline const ecitygml::capi::AbstractCityObjectKindRef* AsFFI() const;
    inline ecitygml::capi::AbstractCityObjectKindRef* AsFFI();
    inline static const ecitygml::AbstractCityObjectKindRef* FromFFI(const ecitygml::capi::AbstractCityObjectKindRef* ptr);
    inline static ecitygml::AbstractCityObjectKindRef* FromFFI(ecitygml::capi::AbstractCityObjectKindRef* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractCityObjectKindRef() = delete;
    AbstractCityObjectKindRef(const ecitygml::AbstractCityObjectKindRef&) = delete;
    AbstractCityObjectKindRef(ecitygml::AbstractCityObjectKindRef&&) noexcept = delete;
    AbstractCityObjectKindRef operator=(const ecitygml::AbstractCityObjectKindRef&) = delete;
    AbstractCityObjectKindRef operator=(ecitygml::AbstractCityObjectKindRef&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AbstractCityObjectKindRef_D_HPP
