#ifndef ecitygml_OccupantTypeValue_HPP
#define ecitygml_OccupantTypeValue_HPP

#include "OccupantTypeValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_OccupantTypeValue_code(const ecitygml::capi::OccupantTypeValue* self);

    diplomat::capi::DiplomatStringView ecitygml_OccupantTypeValue_value(const ecitygml::capi::OccupantTypeValue* self);

    void ecitygml_OccupantTypeValue_destroy(OccupantTypeValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::OccupantTypeValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_OccupantTypeValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::OccupantTypeValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_OccupantTypeValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::OccupantTypeValue* ecitygml::OccupantTypeValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::OccupantTypeValue*>(this);
}

inline ecitygml::capi::OccupantTypeValue* ecitygml::OccupantTypeValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::OccupantTypeValue*>(this);
}

inline const ecitygml::OccupantTypeValue* ecitygml::OccupantTypeValue::FromFFI(const ecitygml::capi::OccupantTypeValue* ptr) {
    return reinterpret_cast<const ecitygml::OccupantTypeValue*>(ptr);
}

inline ecitygml::OccupantTypeValue* ecitygml::OccupantTypeValue::FromFFI(ecitygml::capi::OccupantTypeValue* ptr) {
    return reinterpret_cast<ecitygml::OccupantTypeValue*>(ptr);
}

inline void ecitygml::OccupantTypeValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_OccupantTypeValue_destroy(reinterpret_cast<ecitygml::capi::OccupantTypeValue*>(ptr));
}


#endif // ecitygml_OccupantTypeValue_HPP
