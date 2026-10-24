#ifndef ECITYGML_Reference_D_HPP
#define ECITYGML_Reference_D_HPP

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
namespace capi { struct HRef; }
class HRef;
namespace capi { struct Reference; }
class Reference;
namespace capi { struct TrafficSpaceReference; }
class TrafficSpaceReference;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct Reference;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A reference to an object by `xlink:href`, borrowed from a city model.
 */
class Reference {
public:

  /**
   * An owned copy of a traffic space reference (Rust: `From<&TrafficSpaceReference>`).
   */
  inline static std::unique_ptr<ecitygml::Reference> from_traffic_space_reference(const ecitygml::TrafficSpaceReference& reference);

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::Reference* AsFFI() const;
    inline ecitygml::capi::Reference* AsFFI();
    inline static const ecitygml::Reference* FromFFI(const ecitygml::capi::Reference* ptr);
    inline static ecitygml::Reference* FromFFI(ecitygml::capi::Reference* ptr);
    inline static void operator delete(void* ptr);
private:
    Reference() = delete;
    Reference(const ecitygml::Reference&) = delete;
    Reference(ecitygml::Reference&&) noexcept = delete;
    Reference operator=(const ecitygml::Reference&) = delete;
    Reference operator=(ecitygml::Reference&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_Reference_D_HPP
