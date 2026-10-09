#ifndef ECITYGML_Id_D_HPP
#define ECITYGML_Id_D_HPP

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
    struct Id;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A `gml:id`, borrowed from a city model.
 */
class Id {
public:

  inline std::string_view as_str() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::Id* AsFFI() const;
    inline ecitygml::capi::Id* AsFFI();
    inline static const ecitygml::Id* FromFFI(const ecitygml::capi::Id* ptr);
    inline static ecitygml::Id* FromFFI(ecitygml::capi::Id* ptr);
    inline static void operator delete(void* ptr);
private:
    Id() = delete;
    Id(const ecitygml::Id&) = delete;
    Id(ecitygml::Id&&) noexcept = delete;
    Id operator=(const ecitygml::Id&) = delete;
    Id operator=(ecitygml::Id&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_Id_D_HPP
