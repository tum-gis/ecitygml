#ifndef ecitygml_DirectPosition_HPP
#define ecitygml_DirectPosition_HPP

#include "DirectPosition.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "Error.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    typedef struct ecitygml_DirectPosition_new_result {union {ecitygml::capi::DirectPosition* ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_DirectPosition_new_result;
    ecitygml_DirectPosition_new_result ecitygml_DirectPosition_new(double x, double y, double z);

    double ecitygml_DirectPosition_x(const ecitygml::capi::DirectPosition* self);

    double ecitygml_DirectPosition_y(const ecitygml::capi::DirectPosition* self);

    double ecitygml_DirectPosition_z(const ecitygml::capi::DirectPosition* self);

    void ecitygml_DirectPosition_destroy(DirectPosition* self);

    } // extern "C"
} // namespace capi
} // namespace

inline diplomat::result<std::unique_ptr<ecitygml::DirectPosition>, std::unique_ptr<ecitygml::Error>> ecitygml::DirectPosition::create(double x, double y, double z) {
    auto result = ecitygml::capi::ecitygml_DirectPosition_new(x,
        y,
        z);
    return result.is_ok ? diplomat::result<std::unique_ptr<ecitygml::DirectPosition>, std::unique_ptr<ecitygml::Error>>(diplomat::Ok<std::unique_ptr<ecitygml::DirectPosition>>(std::unique_ptr<ecitygml::DirectPosition>(ecitygml::DirectPosition::FromFFI(result.ok)))) : diplomat::result<std::unique_ptr<ecitygml::DirectPosition>, std::unique_ptr<ecitygml::Error>>(diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline double ecitygml::DirectPosition::x() const {
    auto result = ecitygml::capi::ecitygml_DirectPosition_x(this->AsFFI());
    return result;
}

inline double ecitygml::DirectPosition::y() const {
    auto result = ecitygml::capi::ecitygml_DirectPosition_y(this->AsFFI());
    return result;
}

inline double ecitygml::DirectPosition::z() const {
    auto result = ecitygml::capi::ecitygml_DirectPosition_z(this->AsFFI());
    return result;
}

inline const ecitygml::capi::DirectPosition* ecitygml::DirectPosition::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::DirectPosition*>(this);
}

inline ecitygml::capi::DirectPosition* ecitygml::DirectPosition::AsFFI() {
    return reinterpret_cast<ecitygml::capi::DirectPosition*>(this);
}

inline const ecitygml::DirectPosition* ecitygml::DirectPosition::FromFFI(const ecitygml::capi::DirectPosition* ptr) {
    return reinterpret_cast<const ecitygml::DirectPosition*>(ptr);
}

inline ecitygml::DirectPosition* ecitygml::DirectPosition::FromFFI(ecitygml::capi::DirectPosition* ptr) {
    return reinterpret_cast<ecitygml::DirectPosition*>(ptr);
}

inline void ecitygml::DirectPosition::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_DirectPosition_destroy(reinterpret_cast<ecitygml::capi::DirectPosition*>(ptr));
}


#endif // ecitygml_DirectPosition_HPP
