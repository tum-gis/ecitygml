#ifndef ecitygml_Error_HPP
#define ecitygml_Error_HPP

#include "Error.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "ErrorKind.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    ecitygml::capi::ErrorKind ecitygml_Error_kind(const ecitygml::capi::Error* self);

    void ecitygml_Error_message(const ecitygml::capi::Error* self, diplomat::capi::DiplomatWrite* write);

    void ecitygml_Error_destroy(Error* self);

    } // extern "C"
} // namespace capi
} // namespace

inline ecitygml::ErrorKind ecitygml::Error::kind() const {
    auto result = ecitygml::capi::ecitygml_Error_kind(this->AsFFI());
    return ecitygml::ErrorKind::FromFFI(result);
}

inline std::string ecitygml::Error::message() const {
    std::string output;
    diplomat::capi::DiplomatWrite write = diplomat::WriteFromString(output);
    ecitygml::capi::ecitygml_Error_message(this->AsFFI(),
        &write);
    return output;
}
template<typename W>
inline void ecitygml::Error::message_write(W& writeable) const {
    diplomat::capi::DiplomatWrite write = diplomat::WriteTrait<W>::Construct(writeable);
    ecitygml::capi::ecitygml_Error_message(this->AsFFI(),
        &write);
}

inline const ecitygml::capi::Error* ecitygml::Error::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Error*>(this);
}

inline ecitygml::capi::Error* ecitygml::Error::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Error*>(this);
}

inline const ecitygml::Error* ecitygml::Error::FromFFI(const ecitygml::capi::Error* ptr) {
    return reinterpret_cast<const ecitygml::Error*>(ptr);
}

inline ecitygml::Error* ecitygml::Error::FromFFI(ecitygml::capi::Error* ptr) {
    return reinterpret_cast<ecitygml::Error*>(ptr);
}

inline void ecitygml::Error::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Error_destroy(reinterpret_cast<ecitygml::capi::Error*>(ptr));
}


#endif // ecitygml_Error_HPP
