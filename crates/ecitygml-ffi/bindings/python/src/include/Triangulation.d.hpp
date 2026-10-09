#ifndef ECITYGML_Triangulation_D_HPP
#define ECITYGML_Triangulation_D_HPP

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
namespace capi { struct TriangulatedSurface; }
class TriangulatedSurface;
namespace capi { struct TriangulationSkippedIterator; }
class TriangulationSkippedIterator;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct Triangulation;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A triangulated surface and the members that couldn't be triangulated.
 */
class Triangulation {
public:

  inline const ecitygml::TriangulatedSurface& surface() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * Whether some members couldn't be triangulated.
   */
  inline bool has_skipped() const;

  /**
   * Why members couldn't be triangulated, one error each.
   */
  inline std::unique_ptr<ecitygml::TriangulationSkippedIterator> skipped() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::Triangulation* AsFFI() const;
    inline ecitygml::capi::Triangulation* AsFFI();
    inline static const ecitygml::Triangulation* FromFFI(const ecitygml::capi::Triangulation* ptr);
    inline static ecitygml::Triangulation* FromFFI(ecitygml::capi::Triangulation* ptr);
    inline static void operator delete(void* ptr);
private:
    Triangulation() = delete;
    Triangulation(const ecitygml::Triangulation&) = delete;
    Triangulation(ecitygml::Triangulation&&) noexcept = delete;
    Triangulation operator=(const ecitygml::Triangulation&) = delete;
    Triangulation operator=(ecitygml::Triangulation&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_Triangulation_D_HPP
