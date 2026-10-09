#ifndef ECITYGML_TrafficSpaceUsageValue_HPP
#define ECITYGML_TrafficSpaceUsageValue_HPP

#include "TrafficSpaceUsageValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_TrafficSpaceUsageValue_code(const ecitygml::capi::TrafficSpaceUsageValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_TrafficSpaceUsageValue_value(const ecitygml::capi::TrafficSpaceUsageValue* self);

    void ecitygml_TrafficSpaceUsageValue_destroy(TrafficSpaceUsageValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::TrafficSpaceUsageValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpaceUsageValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::TrafficSpaceUsageValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpaceUsageValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::TrafficSpaceUsageValue* ecitygml::TrafficSpaceUsageValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TrafficSpaceUsageValue*>(this);
}

inline ecitygml::capi::TrafficSpaceUsageValue* ecitygml::TrafficSpaceUsageValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TrafficSpaceUsageValue*>(this);
}

inline const ecitygml::TrafficSpaceUsageValue* ecitygml::TrafficSpaceUsageValue::FromFFI(const ecitygml::capi::TrafficSpaceUsageValue* ptr) {
    return reinterpret_cast<const ecitygml::TrafficSpaceUsageValue*>(ptr);
}

inline ecitygml::TrafficSpaceUsageValue* ecitygml::TrafficSpaceUsageValue::FromFFI(ecitygml::capi::TrafficSpaceUsageValue* ptr) {
    return reinterpret_cast<ecitygml::TrafficSpaceUsageValue*>(ptr);
}

inline void ecitygml::TrafficSpaceUsageValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TrafficSpaceUsageValue_destroy(reinterpret_cast<ecitygml::capi::TrafficSpaceUsageValue*>(ptr));
}


#endif // ECITYGML_TrafficSpaceUsageValue_HPP
