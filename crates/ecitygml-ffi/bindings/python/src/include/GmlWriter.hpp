#ifndef ECITYGML_GmlWriter_HPP
#define ECITYGML_GmlWriter_HPP

#include "GmlWriter.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "CityModel.hpp"
#include "CitygmlFormat.hpp"
#include "Error.hpp"
#include "Formatting.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    typedef struct ecitygml_GmlWriter_from_path_result {union {ecitygml::capi::GmlWriter* ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_GmlWriter_from_path_result;
    ecitygml_GmlWriter_from_path_result ecitygml_GmlWriter_from_path(ecitygml::diplomat::capi::DiplomatStringView path);

    typedef struct ecitygml_GmlWriter_from_base_path_with_format_result {union {ecitygml::capi::GmlWriter* ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_GmlWriter_from_base_path_with_format_result;
    ecitygml_GmlWriter_from_base_path_with_format_result ecitygml_GmlWriter_from_base_path_with_format(ecitygml::diplomat::capi::DiplomatStringView base_path, ecitygml::capi::CitygmlFormat format);

    void ecitygml_GmlWriter_with_formatting(ecitygml::capi::GmlWriter* self, const ecitygml::capi::Formatting* formatting);

    typedef struct ecitygml_GmlWriter_finish_result {union { ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_GmlWriter_finish_result;
    ecitygml_GmlWriter_finish_result ecitygml_GmlWriter_finish(ecitygml::capi::GmlWriter* self, const ecitygml::capi::CityModel* city_model);

    void ecitygml_GmlWriter_destroy(GmlWriter* self);

    } // extern "C"
} // namespace capi
} // namespace

inline ecitygml::diplomat::result<std::unique_ptr<ecitygml::GmlWriter>, std::unique_ptr<ecitygml::Error>> ecitygml::GmlWriter::from_path(std::string_view path) {
    auto result = ecitygml::capi::ecitygml_GmlWriter_from_path({path.data(), path.size()});
    return result.is_ok ? ecitygml::diplomat::result<std::unique_ptr<ecitygml::GmlWriter>, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Ok<std::unique_ptr<ecitygml::GmlWriter>>(std::unique_ptr<ecitygml::GmlWriter>(ecitygml::GmlWriter::FromFFI(result.ok)))) : ecitygml::diplomat::result<std::unique_ptr<ecitygml::GmlWriter>, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline ecitygml::diplomat::result<std::unique_ptr<ecitygml::GmlWriter>, std::unique_ptr<ecitygml::Error>> ecitygml::GmlWriter::from_base_path_with_format(std::string_view base_path, ecitygml::CitygmlFormat format) {
    auto result = ecitygml::capi::ecitygml_GmlWriter_from_base_path_with_format({base_path.data(), base_path.size()},
        format.AsFFI());
    return result.is_ok ? ecitygml::diplomat::result<std::unique_ptr<ecitygml::GmlWriter>, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Ok<std::unique_ptr<ecitygml::GmlWriter>>(std::unique_ptr<ecitygml::GmlWriter>(ecitygml::GmlWriter::FromFFI(result.ok)))) : ecitygml::diplomat::result<std::unique_ptr<ecitygml::GmlWriter>, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline void ecitygml::GmlWriter::with_formatting(const ecitygml::Formatting& formatting) {
    ecitygml::capi::ecitygml_GmlWriter_with_formatting(this->AsFFI(),
        formatting.AsFFI());
}

inline ecitygml::diplomat::result<std::monostate, std::unique_ptr<ecitygml::Error>> ecitygml::GmlWriter::finish(const ecitygml::CityModel& city_model) {
    auto result = ecitygml::capi::ecitygml_GmlWriter_finish(this->AsFFI(),
        city_model.AsFFI());
    return result.is_ok ? ecitygml::diplomat::result<std::monostate, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Ok<std::monostate>()) : ecitygml::diplomat::result<std::monostate, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline const ecitygml::capi::GmlWriter* ecitygml::GmlWriter::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::GmlWriter*>(this);
}

inline ecitygml::capi::GmlWriter* ecitygml::GmlWriter::AsFFI() {
    return reinterpret_cast<ecitygml::capi::GmlWriter*>(this);
}

inline const ecitygml::GmlWriter* ecitygml::GmlWriter::FromFFI(const ecitygml::capi::GmlWriter* ptr) {
    return reinterpret_cast<const ecitygml::GmlWriter*>(ptr);
}

inline ecitygml::GmlWriter* ecitygml::GmlWriter::FromFFI(ecitygml::capi::GmlWriter* ptr) {
    return reinterpret_cast<ecitygml::GmlWriter*>(ptr);
}

inline void ecitygml::GmlWriter::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_GmlWriter_destroy(reinterpret_cast<ecitygml::capi::GmlWriter*>(ptr));
}


#endif // ECITYGML_GmlWriter_HPP
