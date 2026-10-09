#ifndef ECITYGML_SurfaceMaterialValue_D_HPP
#define ECITYGML_SurfaceMaterialValue_D_HPP

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
namespace capi { struct Code; }
class Code;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct SurfaceMaterialValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `surfaceMaterial` property of a TrafficArea or AuxiliaryTrafficArea.
 */
class SurfaceMaterialValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::SurfaceMaterialValue* AsFFI() const;
    inline ecitygml::capi::SurfaceMaterialValue* AsFFI();
    inline static const ecitygml::SurfaceMaterialValue* FromFFI(const ecitygml::capi::SurfaceMaterialValue* ptr);
    inline static ecitygml::SurfaceMaterialValue* FromFFI(ecitygml::capi::SurfaceMaterialValue* ptr);
    inline static void operator delete(void* ptr);
private:
    SurfaceMaterialValue() = delete;
    SurfaceMaterialValue(const ecitygml::SurfaceMaterialValue&) = delete;
    SurfaceMaterialValue(ecitygml::SurfaceMaterialValue&&) noexcept = delete;
    SurfaceMaterialValue operator=(const ecitygml::SurfaceMaterialValue&) = delete;
    SurfaceMaterialValue operator=(ecitygml::SurfaceMaterialValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_SurfaceMaterialValue_D_HPP
