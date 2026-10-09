#ifndef ecitygml_TrafficSpaceClassValue_D_HPP
#define ecitygml_TrafficSpaceClassValue_D_HPP

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
    struct TrafficSpaceClassValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `class` property of a TrafficSpace.
 */
class TrafficSpaceClassValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TrafficSpaceClassValue* AsFFI() const;
    inline ecitygml::capi::TrafficSpaceClassValue* AsFFI();
    inline static const ecitygml::TrafficSpaceClassValue* FromFFI(const ecitygml::capi::TrafficSpaceClassValue* ptr);
    inline static ecitygml::TrafficSpaceClassValue* FromFFI(ecitygml::capi::TrafficSpaceClassValue* ptr);
    inline static void operator delete(void* ptr);
private:
    TrafficSpaceClassValue() = delete;
    TrafficSpaceClassValue(const ecitygml::TrafficSpaceClassValue&) = delete;
    TrafficSpaceClassValue(ecitygml::TrafficSpaceClassValue&&) noexcept = delete;
    TrafficSpaceClassValue operator=(const ecitygml::TrafficSpaceClassValue&) = delete;
    TrafficSpaceClassValue operator=(ecitygml::TrafficSpaceClassValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_TrafficSpaceClassValue_D_HPP
