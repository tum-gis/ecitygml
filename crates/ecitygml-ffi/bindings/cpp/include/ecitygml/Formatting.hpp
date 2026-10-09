#ifndef ecitygml_Formatting_HPP
#define ecitygml_Formatting_HPP

#include "Formatting.d.hpp"

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

    ecitygml::capi::Formatting* ecitygml_Formatting_compact(void);

    ecitygml::capi::Formatting* ecitygml_Formatting_new_line(void);

    ecitygml::capi::Formatting* ecitygml_Formatting_indent(uint8_t char_, size_t size);

    void ecitygml_Formatting_destroy(Formatting* self);

    } // extern "C"
} // namespace capi
} // namespace

inline std::unique_ptr<ecitygml::Formatting> ecitygml::Formatting::compact() {
    auto result = ecitygml::capi::ecitygml_Formatting_compact();
    return std::unique_ptr<ecitygml::Formatting>(ecitygml::Formatting::FromFFI(result));
}

inline std::unique_ptr<ecitygml::Formatting> ecitygml::Formatting::new_line() {
    auto result = ecitygml::capi::ecitygml_Formatting_new_line();
    return std::unique_ptr<ecitygml::Formatting>(ecitygml::Formatting::FromFFI(result));
}

inline std::unique_ptr<ecitygml::Formatting> ecitygml::Formatting::indent(uint8_t char_, size_t size) {
    auto result = ecitygml::capi::ecitygml_Formatting_indent(char_,
        size);
    return std::unique_ptr<ecitygml::Formatting>(ecitygml::Formatting::FromFFI(result));
}

inline const ecitygml::capi::Formatting* ecitygml::Formatting::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Formatting*>(this);
}

inline ecitygml::capi::Formatting* ecitygml::Formatting::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Formatting*>(this);
}

inline const ecitygml::Formatting* ecitygml::Formatting::FromFFI(const ecitygml::capi::Formatting* ptr) {
    return reinterpret_cast<const ecitygml::Formatting*>(ptr);
}

inline ecitygml::Formatting* ecitygml::Formatting::FromFFI(ecitygml::capi::Formatting* ptr) {
    return reinterpret_cast<ecitygml::Formatting*>(ptr);
}

inline void ecitygml::Formatting::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Formatting_destroy(reinterpret_cast<ecitygml::capi::Formatting*>(ptr));
}


#endif // ecitygml_Formatting_HPP
