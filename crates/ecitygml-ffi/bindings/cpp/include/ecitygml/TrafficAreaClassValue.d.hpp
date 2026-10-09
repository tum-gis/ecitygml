#ifndef ecitygml_TrafficAreaClassValue_D_HPP
#define ecitygml_TrafficAreaClassValue_D_HPP

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
namespace capi { struct Code; }
class Code;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct TrafficAreaClassValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `class` property of a TrafficArea.
 */
class TrafficAreaClassValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TrafficAreaClassValue* AsFFI() const;
    inline ecitygml::capi::TrafficAreaClassValue* AsFFI();
    inline static const ecitygml::TrafficAreaClassValue* FromFFI(const ecitygml::capi::TrafficAreaClassValue* ptr);
    inline static ecitygml::TrafficAreaClassValue* FromFFI(ecitygml::capi::TrafficAreaClassValue* ptr);
    inline static void operator delete(void* ptr);
private:
    TrafficAreaClassValue() = delete;
    TrafficAreaClassValue(const ecitygml::TrafficAreaClassValue&) = delete;
    TrafficAreaClassValue(ecitygml::TrafficAreaClassValue&&) noexcept = delete;
    TrafficAreaClassValue operator=(const ecitygml::TrafficAreaClassValue&) = delete;
    TrafficAreaClassValue operator=(ecitygml::TrafficAreaClassValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_TrafficAreaClassValue_D_HPP
