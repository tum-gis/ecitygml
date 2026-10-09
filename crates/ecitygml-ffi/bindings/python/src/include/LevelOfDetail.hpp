#ifndef ECITYGML_LevelOfDetail_HPP
#define ECITYGML_LevelOfDetail_HPP

#include "LevelOfDetail.d.hpp"

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

    size_t ecitygml_LevelOfDetail_as_index(ecitygml::capi::LevelOfDetail self);

    typedef struct ecitygml_LevelOfDetail_try_from_result {union {ecitygml::capi::LevelOfDetail ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_LevelOfDetail_try_from_result;
    ecitygml_LevelOfDetail_try_from_result ecitygml_LevelOfDetail_try_from(uint8_t value);

    } // extern "C"
} // namespace capi
} // namespace

inline ecitygml::capi::LevelOfDetail ecitygml::LevelOfDetail::AsFFI() const {
    return static_cast<ecitygml::capi::LevelOfDetail>(value);
}

inline ecitygml::LevelOfDetail ecitygml::LevelOfDetail::FromFFI(ecitygml::capi::LevelOfDetail c_enum) {
    switch (c_enum) {
        case ecitygml::capi::LevelOfDetail_Zero:
        case ecitygml::capi::LevelOfDetail_One:
        case ecitygml::capi::LevelOfDetail_Two:
        case ecitygml::capi::LevelOfDetail_Three:
            return static_cast<ecitygml::LevelOfDetail::Value>(c_enum);
        default:
            std::abort();
    }
}

inline size_t ecitygml::LevelOfDetail::as_index() const {
    auto result = ecitygml::capi::ecitygml_LevelOfDetail_as_index(this->AsFFI());
    return result;
}

inline ecitygml::diplomat::result<ecitygml::LevelOfDetail, std::unique_ptr<ecitygml::Error>> ecitygml::LevelOfDetail::try_from(uint8_t value) {
    auto result = ecitygml::capi::ecitygml_LevelOfDetail_try_from(value);
    return result.is_ok ? ecitygml::diplomat::result<ecitygml::LevelOfDetail, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Ok<ecitygml::LevelOfDetail>(ecitygml::LevelOfDetail::FromFFI(result.ok))) : ecitygml::diplomat::result<ecitygml::LevelOfDetail, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}
#endif // ECITYGML_LevelOfDetail_HPP
