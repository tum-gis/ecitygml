#ifndef ECITYGML_OccupantTypeValue_D_HPP
#define ECITYGML_OccupantTypeValue_D_HPP

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
    struct OccupantTypeValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `occupantType` property of an Occupancy.
 */
class OccupantTypeValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::OccupantTypeValue* AsFFI() const;
    inline ecitygml::capi::OccupantTypeValue* AsFFI();
    inline static const ecitygml::OccupantTypeValue* FromFFI(const ecitygml::capi::OccupantTypeValue* ptr);
    inline static ecitygml::OccupantTypeValue* FromFFI(ecitygml::capi::OccupantTypeValue* ptr);
    inline static void operator delete(void* ptr);
private:
    OccupantTypeValue() = delete;
    OccupantTypeValue(const ecitygml::OccupantTypeValue&) = delete;
    OccupantTypeValue(ecitygml::OccupantTypeValue&&) noexcept = delete;
    OccupantTypeValue operator=(const ecitygml::OccupantTypeValue&) = delete;
    OccupantTypeValue operator=(ecitygml::OccupantTypeValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_OccupantTypeValue_D_HPP
