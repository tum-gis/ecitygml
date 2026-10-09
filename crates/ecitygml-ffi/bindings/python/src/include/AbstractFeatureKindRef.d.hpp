#ifndef ECITYGML_AbstractFeatureKindRef_D_HPP
#define ECITYGML_AbstractFeatureKindRef_D_HPP

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
namespace capi { struct AbstractCityObjectKindRef; }
class AbstractCityObjectKindRef;
namespace capi { struct AbstractFeatureKindRef; }
class AbstractFeatureKindRef;
namespace capi { struct AbstractSpaceBoundaryKind; }
class AbstractSpaceBoundaryKind;
class FeatureType;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct AbstractFeatureKindRef;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A reference to a feature of any type; convert it with e.g. `TrafficSpace::try_from`.
 */
class AbstractFeatureKindRef {
public:

  /**
   * The feature a space boundary is (Rust: `From<&AbstractSpaceBoundaryKind>`), to convert it
   * with e.g. `WallSurface::try_from`.
   */
  inline static std::unique_ptr<ecitygml::AbstractFeatureKindRef> from_space_boundary(const ecitygml::AbstractSpaceBoundaryKind& boundary DIPLOMAT_LIFETIME_BOUND);

  /**
   * The feature a city object is, to convert it with e.g. `Building::try_from` (Rust wraps it in
   * the `AbstractFeatureWithLifespanKind(AbstractCityObjectKind(_))` variants; it has no `From`).
   */
  inline static std::unique_ptr<ecitygml::AbstractFeatureKindRef> from_city_object(const ecitygml::AbstractCityObjectKindRef& city_object DIPLOMAT_LIFETIME_BOUND);

  inline ecitygml::FeatureType feature_type() const;

    inline const ecitygml::capi::AbstractFeatureKindRef* AsFFI() const;
    inline ecitygml::capi::AbstractFeatureKindRef* AsFFI();
    inline static const ecitygml::AbstractFeatureKindRef* FromFFI(const ecitygml::capi::AbstractFeatureKindRef* ptr);
    inline static ecitygml::AbstractFeatureKindRef* FromFFI(ecitygml::capi::AbstractFeatureKindRef* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractFeatureKindRef() = delete;
    AbstractFeatureKindRef(const ecitygml::AbstractFeatureKindRef&) = delete;
    AbstractFeatureKindRef(ecitygml::AbstractFeatureKindRef&&) noexcept = delete;
    AbstractFeatureKindRef operator=(const ecitygml::AbstractFeatureKindRef&) = delete;
    AbstractFeatureKindRef operator=(ecitygml::AbstractFeatureKindRef&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AbstractFeatureKindRef_D_HPP
