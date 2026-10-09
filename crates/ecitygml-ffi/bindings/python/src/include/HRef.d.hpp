#ifndef ECITYGML_HRef_D_HPP
#define ECITYGML_HRef_D_HPP

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
namespace capi {
    struct HRef;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * An `xlink:href` reference (local `#id` or remote URI), borrowed from a city model.
 */
class HRef {
public:

  /**
   * The referenced `gml:id` of a local reference (`#id`), or none for a remote one.
   */
  inline std::optional<std::string_view> local_id() const DIPLOMAT_LIFETIME_BOUND;

  inline bool is_local() const;

  /**
   * The reference as written in GML (Rust: `Display`).
   */
  inline std::string to_string() const;
  template<typename W>
  inline void to_string_write(W& writeable_output) const;

    inline const ecitygml::capi::HRef* AsFFI() const;
    inline ecitygml::capi::HRef* AsFFI();
    inline static const ecitygml::HRef* FromFFI(const ecitygml::capi::HRef* ptr);
    inline static ecitygml::HRef* FromFFI(ecitygml::capi::HRef* ptr);
    inline static void operator delete(void* ptr);
private:
    HRef() = delete;
    HRef(const ecitygml::HRef&) = delete;
    HRef(ecitygml::HRef&&) noexcept = delete;
    HRef operator=(const ecitygml::HRef&) = delete;
    HRef operator=(ecitygml::HRef&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_HRef_D_HPP
