#ifndef ECITYGML_RoadClassValue_D_HPP
#define ECITYGML_RoadClassValue_D_HPP

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
    struct RoadClassValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `class` property of a Road.
 */
class RoadClassValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::RoadClassValue* AsFFI() const;
    inline ecitygml::capi::RoadClassValue* AsFFI();
    inline static const ecitygml::RoadClassValue* FromFFI(const ecitygml::capi::RoadClassValue* ptr);
    inline static ecitygml::RoadClassValue* FromFFI(ecitygml::capi::RoadClassValue* ptr);
    inline static void operator delete(void* ptr);
private:
    RoadClassValue() = delete;
    RoadClassValue(const ecitygml::RoadClassValue&) = delete;
    RoadClassValue(ecitygml::RoadClassValue&&) noexcept = delete;
    RoadClassValue operator=(const ecitygml::RoadClassValue&) = delete;
    RoadClassValue operator=(ecitygml::RoadClassValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_RoadClassValue_D_HPP
