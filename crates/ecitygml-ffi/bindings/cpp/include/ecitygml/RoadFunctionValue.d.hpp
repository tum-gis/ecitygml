#ifndef ecitygml_RoadFunctionValue_D_HPP
#define ecitygml_RoadFunctionValue_D_HPP

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
    struct RoadFunctionValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `function` property of a Road.
 */
class RoadFunctionValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::RoadFunctionValue* AsFFI() const;
    inline ecitygml::capi::RoadFunctionValue* AsFFI();
    inline static const ecitygml::RoadFunctionValue* FromFFI(const ecitygml::capi::RoadFunctionValue* ptr);
    inline static ecitygml::RoadFunctionValue* FromFFI(ecitygml::capi::RoadFunctionValue* ptr);
    inline static void operator delete(void* ptr);
private:
    RoadFunctionValue() = delete;
    RoadFunctionValue(const ecitygml::RoadFunctionValue&) = delete;
    RoadFunctionValue(ecitygml::RoadFunctionValue&&) noexcept = delete;
    RoadFunctionValue operator=(const ecitygml::RoadFunctionValue&) = delete;
    RoadFunctionValue operator=(ecitygml::RoadFunctionValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_RoadFunctionValue_D_HPP
