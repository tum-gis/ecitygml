#ifndef ECITYGML_PlantCoverClassValue_D_HPP
#define ECITYGML_PlantCoverClassValue_D_HPP

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
    struct PlantCoverClassValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `class` property of a PlantCover.
 */
class PlantCoverClassValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::PlantCoverClassValue* AsFFI() const;
    inline ecitygml::capi::PlantCoverClassValue* AsFFI();
    inline static const ecitygml::PlantCoverClassValue* FromFFI(const ecitygml::capi::PlantCoverClassValue* ptr);
    inline static ecitygml::PlantCoverClassValue* FromFFI(ecitygml::capi::PlantCoverClassValue* ptr);
    inline static void operator delete(void* ptr);
private:
    PlantCoverClassValue() = delete;
    PlantCoverClassValue(const ecitygml::PlantCoverClassValue&) = delete;
    PlantCoverClassValue(ecitygml::PlantCoverClassValue&&) noexcept = delete;
    PlantCoverClassValue operator=(const ecitygml::PlantCoverClassValue&) = delete;
    PlantCoverClassValue operator=(ecitygml::PlantCoverClassValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_PlantCoverClassValue_D_HPP
