#ifndef ecitygml_HRef_HPP
#define ecitygml_HRef_HPP

#include "HRef.d.hpp"

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
namespace capi {
    extern "C" {

    typedef struct ecitygml_HRef_local_id_result {union {diplomat::capi::DiplomatStringView ok; }; bool is_ok;} ecitygml_HRef_local_id_result;
    ecitygml_HRef_local_id_result ecitygml_HRef_local_id(const ecitygml::capi::HRef* self);

    bool ecitygml_HRef_is_local(const ecitygml::capi::HRef* self);

    void ecitygml_HRef_to_string(const ecitygml::capi::HRef* self, diplomat::capi::DiplomatWrite* write);

    void ecitygml_HRef_destroy(HRef* self);

    } // extern "C"
} // namespace capi
} // namespace

inline std::optional<std::string_view> ecitygml::HRef::local_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_HRef_local_id(this->AsFFI());
    return result.is_ok ? std::optional<std::string_view>(std::string_view(result.ok.data, result.ok.len)) : std::nullopt;
}

inline bool ecitygml::HRef::is_local() const {
    auto result = ecitygml::capi::ecitygml_HRef_is_local(this->AsFFI());
    return result;
}

inline std::string ecitygml::HRef::to_string() const {
    std::string output;
    diplomat::capi::DiplomatWrite write = diplomat::WriteFromString(output);
    ecitygml::capi::ecitygml_HRef_to_string(this->AsFFI(),
        &write);
    return output;
}
template<typename W>
inline void ecitygml::HRef::to_string_write(W& writeable) const {
    diplomat::capi::DiplomatWrite write = diplomat::WriteTrait<W>::Construct(writeable);
    ecitygml::capi::ecitygml_HRef_to_string(this->AsFFI(),
        &write);
}

inline const ecitygml::capi::HRef* ecitygml::HRef::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::HRef*>(this);
}

inline ecitygml::capi::HRef* ecitygml::HRef::AsFFI() {
    return reinterpret_cast<ecitygml::capi::HRef*>(this);
}

inline const ecitygml::HRef* ecitygml::HRef::FromFFI(const ecitygml::capi::HRef* ptr) {
    return reinterpret_cast<const ecitygml::HRef*>(ptr);
}

inline ecitygml::HRef* ecitygml::HRef::FromFFI(ecitygml::capi::HRef* ptr) {
    return reinterpret_cast<ecitygml::HRef*>(ptr);
}

inline void ecitygml::HRef::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_HRef_destroy(reinterpret_cast<ecitygml::capi::HRef*>(ptr));
}


#endif // ecitygml_HRef_HPP
