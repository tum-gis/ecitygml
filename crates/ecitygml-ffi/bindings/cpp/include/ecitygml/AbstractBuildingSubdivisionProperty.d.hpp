#ifndef ecitygml_AbstractBuildingSubdivisionProperty_D_HPP
#define ecitygml_AbstractBuildingSubdivisionProperty_D_HPP

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
namespace capi { struct AbstractBuildingSubdivisionKind; }
class AbstractBuildingSubdivisionKind;
namespace capi { struct HRef; }
class HRef;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct AbstractBuildingSubdivisionProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A building subdivision property (inline building subdivision and/or `xlink:href`), borrowed from a city model.
 */
class AbstractBuildingSubdivisionProperty {
public:

  /**
   * The inline building subdivision; none if the property only references one via `href`.
   */
  inline const ecitygml::AbstractBuildingSubdivisionKind* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AbstractBuildingSubdivisionProperty* AsFFI() const;
    inline ecitygml::capi::AbstractBuildingSubdivisionProperty* AsFFI();
    inline static const ecitygml::AbstractBuildingSubdivisionProperty* FromFFI(const ecitygml::capi::AbstractBuildingSubdivisionProperty* ptr);
    inline static ecitygml::AbstractBuildingSubdivisionProperty* FromFFI(ecitygml::capi::AbstractBuildingSubdivisionProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractBuildingSubdivisionProperty() = delete;
    AbstractBuildingSubdivisionProperty(const ecitygml::AbstractBuildingSubdivisionProperty&) = delete;
    AbstractBuildingSubdivisionProperty(ecitygml::AbstractBuildingSubdivisionProperty&&) noexcept = delete;
    AbstractBuildingSubdivisionProperty operator=(const ecitygml::AbstractBuildingSubdivisionProperty&) = delete;
    AbstractBuildingSubdivisionProperty operator=(ecitygml::AbstractBuildingSubdivisionProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_AbstractBuildingSubdivisionProperty_D_HPP
