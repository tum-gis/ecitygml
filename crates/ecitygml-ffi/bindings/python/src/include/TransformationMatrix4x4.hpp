#ifndef ECITYGML_TransformationMatrix4x4_HPP
#define ECITYGML_TransformationMatrix4x4_HPP

#include "TransformationMatrix4x4.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "Error.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    typedef struct ecitygml_TransformationMatrix4x4_get_result {union {double ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_TransformationMatrix4x4_get_result;
    ecitygml_TransformationMatrix4x4_get_result ecitygml_TransformationMatrix4x4_get(const ecitygml::capi::TransformationMatrix4x4* self, size_t row, size_t column);

    void ecitygml_TransformationMatrix4x4_destroy(TransformationMatrix4x4* self);

    } // extern "C"
} // namespace capi
} // namespace

inline ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>> ecitygml::TransformationMatrix4x4::get(size_t row, size_t column) const {
    auto result = ecitygml::capi::ecitygml_TransformationMatrix4x4_get(this->AsFFI(),
        row,
        column);
    return result.is_ok ? ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Ok<double>(result.ok)) : ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline const ecitygml::capi::TransformationMatrix4x4* ecitygml::TransformationMatrix4x4::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TransformationMatrix4x4*>(this);
}

inline ecitygml::capi::TransformationMatrix4x4* ecitygml::TransformationMatrix4x4::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TransformationMatrix4x4*>(this);
}

inline const ecitygml::TransformationMatrix4x4* ecitygml::TransformationMatrix4x4::FromFFI(const ecitygml::capi::TransformationMatrix4x4* ptr) {
    return reinterpret_cast<const ecitygml::TransformationMatrix4x4*>(ptr);
}

inline ecitygml::TransformationMatrix4x4* ecitygml::TransformationMatrix4x4::FromFFI(ecitygml::capi::TransformationMatrix4x4* ptr) {
    return reinterpret_cast<ecitygml::TransformationMatrix4x4*>(ptr);
}

inline void ecitygml::TransformationMatrix4x4::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TransformationMatrix4x4_destroy(reinterpret_cast<ecitygml::capi::TransformationMatrix4x4*>(ptr));
}


#endif // ECITYGML_TransformationMatrix4x4_HPP
