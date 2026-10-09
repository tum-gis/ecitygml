#ifndef ECITYGML_Code_HPP
#define ECITYGML_Code_HPP

#include "Code.d.hpp"

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

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_Code_value(const ecitygml::capi::Code* self);

    typedef struct ecitygml_Code_code_space_result {union {ecitygml::diplomat::capi::DiplomatStringView ok; }; bool is_ok;} ecitygml_Code_code_space_result;
    ecitygml_Code_code_space_result ecitygml_Code_code_space(const ecitygml::capi::Code* self);

    void ecitygml_Code_destroy(Code* self);

    } // extern "C"
} // namespace capi
} // namespace

inline std::string_view ecitygml::Code::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Code_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline std::optional<std::string_view> ecitygml::Code::code_space() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Code_code_space(this->AsFFI());
    return result.is_ok ? std::optional<std::string_view>(std::string_view(result.ok.data, result.ok.len)) : std::nullopt;
}

inline const ecitygml::capi::Code* ecitygml::Code::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Code*>(this);
}

inline ecitygml::capi::Code* ecitygml::Code::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Code*>(this);
}

inline const ecitygml::Code* ecitygml::Code::FromFFI(const ecitygml::capi::Code* ptr) {
    return reinterpret_cast<const ecitygml::Code*>(ptr);
}

inline ecitygml::Code* ecitygml::Code::FromFFI(ecitygml::capi::Code* ptr) {
    return reinterpret_cast<ecitygml::Code*>(ptr);
}

inline void ecitygml::Code::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Code_destroy(reinterpret_cast<ecitygml::capi::Code*>(ptr));
}


#endif // ECITYGML_Code_HPP
