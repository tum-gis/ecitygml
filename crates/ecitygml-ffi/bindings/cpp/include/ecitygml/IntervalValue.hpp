#ifndef ecitygml_IntervalValue_HPP
#define ecitygml_IntervalValue_HPP

#include "IntervalValue.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "Code.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Code* ecitygml_IntervalValue_code(const ecitygml::capi::IntervalValue* self);

    diplomat::capi::DiplomatStringView ecitygml_IntervalValue_value(const ecitygml::capi::IntervalValue* self);

    void ecitygml_IntervalValue_destroy(IntervalValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::IntervalValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_IntervalValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::IntervalValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_IntervalValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::IntervalValue* ecitygml::IntervalValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::IntervalValue*>(this);
}

inline ecitygml::capi::IntervalValue* ecitygml::IntervalValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::IntervalValue*>(this);
}

inline const ecitygml::IntervalValue* ecitygml::IntervalValue::FromFFI(const ecitygml::capi::IntervalValue* ptr) {
    return reinterpret_cast<const ecitygml::IntervalValue*>(ptr);
}

inline ecitygml::IntervalValue* ecitygml::IntervalValue::FromFFI(ecitygml::capi::IntervalValue* ptr) {
    return reinterpret_cast<ecitygml::IntervalValue*>(ptr);
}

inline void ecitygml::IntervalValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_IntervalValue_destroy(reinterpret_cast<ecitygml::capi::IntervalValue*>(ptr));
}


#endif // ecitygml_IntervalValue_HPP
