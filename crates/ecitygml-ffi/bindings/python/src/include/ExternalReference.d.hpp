#ifndef ECITYGML_ExternalReference_D_HPP
#define ECITYGML_ExternalReference_D_HPP

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
    struct ExternalReference;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A reference to an object in another information system, borrowed from a city model.
 */
class ExternalReference {
public:

  inline std::string_view target_resource() const DIPLOMAT_LIFETIME_BOUND;

  inline std::optional<std::string_view> information_system() const DIPLOMAT_LIFETIME_BOUND;

  inline std::optional<std::string_view> relation_type() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::ExternalReference* AsFFI() const;
    inline ecitygml::capi::ExternalReference* AsFFI();
    inline static const ecitygml::ExternalReference* FromFFI(const ecitygml::capi::ExternalReference* ptr);
    inline static ecitygml::ExternalReference* FromFFI(ecitygml::capi::ExternalReference* ptr);
    inline static void operator delete(void* ptr);
private:
    ExternalReference() = delete;
    ExternalReference(const ecitygml::ExternalReference&) = delete;
    ExternalReference(ecitygml::ExternalReference&&) noexcept = delete;
    ExternalReference operator=(const ecitygml::ExternalReference&) = delete;
    ExternalReference operator=(ecitygml::ExternalReference&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_ExternalReference_D_HPP
