#ifndef ecitygml_IntervalValue_D_HPP
#define ecitygml_IntervalValue_D_HPP

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
    struct IntervalValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `interval` property of an Occupancy.
 */
class IntervalValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::IntervalValue* AsFFI() const;
    inline ecitygml::capi::IntervalValue* AsFFI();
    inline static const ecitygml::IntervalValue* FromFFI(const ecitygml::capi::IntervalValue* ptr);
    inline static ecitygml::IntervalValue* FromFFI(ecitygml::capi::IntervalValue* ptr);
    inline static void operator delete(void* ptr);
private:
    IntervalValue() = delete;
    IntervalValue(const ecitygml::IntervalValue&) = delete;
    IntervalValue(ecitygml::IntervalValue&&) noexcept = delete;
    IntervalValue operator=(const ecitygml::IntervalValue&) = delete;
    IntervalValue operator=(ecitygml::IntervalValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_IntervalValue_D_HPP
