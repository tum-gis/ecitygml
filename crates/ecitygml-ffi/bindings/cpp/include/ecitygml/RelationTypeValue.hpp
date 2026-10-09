#ifndef ecitygml_RelationTypeValue_HPP
#define ecitygml_RelationTypeValue_HPP

#include "RelationTypeValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_RelationTypeValue_code(const ecitygml::capi::RelationTypeValue* self);

    diplomat::capi::DiplomatStringView ecitygml_RelationTypeValue_value(const ecitygml::capi::RelationTypeValue* self);

    void ecitygml_RelationTypeValue_destroy(RelationTypeValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::RelationTypeValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RelationTypeValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::RelationTypeValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RelationTypeValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::RelationTypeValue* ecitygml::RelationTypeValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::RelationTypeValue*>(this);
}

inline ecitygml::capi::RelationTypeValue* ecitygml::RelationTypeValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::RelationTypeValue*>(this);
}

inline const ecitygml::RelationTypeValue* ecitygml::RelationTypeValue::FromFFI(const ecitygml::capi::RelationTypeValue* ptr) {
    return reinterpret_cast<const ecitygml::RelationTypeValue*>(ptr);
}

inline ecitygml::RelationTypeValue* ecitygml::RelationTypeValue::FromFFI(ecitygml::capi::RelationTypeValue* ptr) {
    return reinterpret_cast<ecitygml::RelationTypeValue*>(ptr);
}

inline void ecitygml::RelationTypeValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_RelationTypeValue_destroy(reinterpret_cast<ecitygml::capi::RelationTypeValue*>(ptr));
}


#endif // ecitygml_RelationTypeValue_HPP
