#ifndef ecitygml_PlantCoverUsageValue_HPP
#define ecitygml_PlantCoverUsageValue_HPP

#include "PlantCoverUsageValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_PlantCoverUsageValue_code(const ecitygml::capi::PlantCoverUsageValue* self);

    diplomat::capi::DiplomatStringView ecitygml_PlantCoverUsageValue_value(const ecitygml::capi::PlantCoverUsageValue* self);

    void ecitygml_PlantCoverUsageValue_destroy(PlantCoverUsageValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::PlantCoverUsageValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCoverUsageValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::PlantCoverUsageValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCoverUsageValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::PlantCoverUsageValue* ecitygml::PlantCoverUsageValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::PlantCoverUsageValue*>(this);
}

inline ecitygml::capi::PlantCoverUsageValue* ecitygml::PlantCoverUsageValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::PlantCoverUsageValue*>(this);
}

inline const ecitygml::PlantCoverUsageValue* ecitygml::PlantCoverUsageValue::FromFFI(const ecitygml::capi::PlantCoverUsageValue* ptr) {
    return reinterpret_cast<const ecitygml::PlantCoverUsageValue*>(ptr);
}

inline ecitygml::PlantCoverUsageValue* ecitygml::PlantCoverUsageValue::FromFFI(ecitygml::capi::PlantCoverUsageValue* ptr) {
    return reinterpret_cast<ecitygml::PlantCoverUsageValue*>(ptr);
}

inline void ecitygml::PlantCoverUsageValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_PlantCoverUsageValue_destroy(reinterpret_cast<ecitygml::capi::PlantCoverUsageValue*>(ptr));
}


#endif // ecitygml_PlantCoverUsageValue_HPP
