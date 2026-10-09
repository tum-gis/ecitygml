#ifndef ECITYGML_RoadUsageValue_HPP
#define ECITYGML_RoadUsageValue_HPP

#include "RoadUsageValue.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "Code.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Code* ecitygml_RoadUsageValue_code(const ecitygml::capi::RoadUsageValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_RoadUsageValue_value(const ecitygml::capi::RoadUsageValue* self);

    void ecitygml_RoadUsageValue_destroy(RoadUsageValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::RoadUsageValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoadUsageValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::RoadUsageValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoadUsageValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::RoadUsageValue* ecitygml::RoadUsageValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::RoadUsageValue*>(this);
}

inline ecitygml::capi::RoadUsageValue* ecitygml::RoadUsageValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::RoadUsageValue*>(this);
}

inline const ecitygml::RoadUsageValue* ecitygml::RoadUsageValue::FromFFI(const ecitygml::capi::RoadUsageValue* ptr) {
    return reinterpret_cast<const ecitygml::RoadUsageValue*>(ptr);
}

inline ecitygml::RoadUsageValue* ecitygml::RoadUsageValue::FromFFI(ecitygml::capi::RoadUsageValue* ptr) {
    return reinterpret_cast<ecitygml::RoadUsageValue*>(ptr);
}

inline void ecitygml::RoadUsageValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_RoadUsageValue_destroy(reinterpret_cast<ecitygml::capi::RoadUsageValue*>(ptr));
}


#endif // ECITYGML_RoadUsageValue_HPP
