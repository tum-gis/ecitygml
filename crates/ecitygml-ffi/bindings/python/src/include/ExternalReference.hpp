#ifndef ECITYGML_ExternalReference_HPP
#define ECITYGML_ExternalReference_HPP

#include "ExternalReference.d.hpp"

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
namespace capi {
    extern "C" {

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_ExternalReference_target_resource(const ecitygml::capi::ExternalReference* self);

    typedef struct ecitygml_ExternalReference_information_system_result {union {ecitygml::diplomat::capi::DiplomatStringView ok; }; bool is_ok;} ecitygml_ExternalReference_information_system_result;
    ecitygml_ExternalReference_information_system_result ecitygml_ExternalReference_information_system(const ecitygml::capi::ExternalReference* self);

    typedef struct ecitygml_ExternalReference_relation_type_result {union {ecitygml::diplomat::capi::DiplomatStringView ok; }; bool is_ok;} ecitygml_ExternalReference_relation_type_result;
    ecitygml_ExternalReference_relation_type_result ecitygml_ExternalReference_relation_type(const ecitygml::capi::ExternalReference* self);

    void ecitygml_ExternalReference_destroy(ExternalReference* self);

    } // extern "C"
} // namespace capi
} // namespace

inline std::string_view ecitygml::ExternalReference::target_resource() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ExternalReference_target_resource(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline std::optional<std::string_view> ecitygml::ExternalReference::information_system() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ExternalReference_information_system(this->AsFFI());
    return result.is_ok ? std::optional<std::string_view>(std::string_view(result.ok.data, result.ok.len)) : std::nullopt;
}

inline std::optional<std::string_view> ecitygml::ExternalReference::relation_type() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ExternalReference_relation_type(this->AsFFI());
    return result.is_ok ? std::optional<std::string_view>(std::string_view(result.ok.data, result.ok.len)) : std::nullopt;
}

inline const ecitygml::capi::ExternalReference* ecitygml::ExternalReference::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::ExternalReference*>(this);
}

inline ecitygml::capi::ExternalReference* ecitygml::ExternalReference::AsFFI() {
    return reinterpret_cast<ecitygml::capi::ExternalReference*>(this);
}

inline const ecitygml::ExternalReference* ecitygml::ExternalReference::FromFFI(const ecitygml::capi::ExternalReference* ptr) {
    return reinterpret_cast<const ecitygml::ExternalReference*>(ptr);
}

inline ecitygml::ExternalReference* ecitygml::ExternalReference::FromFFI(ecitygml::capi::ExternalReference* ptr) {
    return reinterpret_cast<ecitygml::ExternalReference*>(ptr);
}

inline void ecitygml::ExternalReference::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_ExternalReference_destroy(reinterpret_cast<ecitygml::capi::ExternalReference*>(ptr));
}


#endif // ECITYGML_ExternalReference_HPP
