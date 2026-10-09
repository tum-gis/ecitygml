#ifndef ecitygml_GmlReader_HPP
#define ecitygml_GmlReader_HPP

#include "GmlReader.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "CityModel.hpp"
#include "CitygmlFormat.hpp"
#include "Error.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    ecitygml::capi::GmlReader* ecitygml_GmlReader_new(diplomat::capi::DiplomatU8View data, ecitygml::capi::CitygmlFormat format);

    typedef struct ecitygml_GmlReader_from_path_result {union {ecitygml::capi::GmlReader* ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_GmlReader_from_path_result;
    ecitygml_GmlReader_from_path_result ecitygml_GmlReader_from_path(diplomat::capi::DiplomatStringView path);

    void ecitygml_GmlReader_with_rebuild_object_bounds(ecitygml::capi::GmlReader* self, bool rebuild_object_bounds);

    typedef struct ecitygml_GmlReader_finish_result {union {ecitygml::capi::CityModel* ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_GmlReader_finish_result;
    ecitygml_GmlReader_finish_result ecitygml_GmlReader_finish(ecitygml::capi::GmlReader* self);

    void ecitygml_GmlReader_destroy(GmlReader* self);

    } // extern "C"
} // namespace capi
} // namespace

inline std::unique_ptr<ecitygml::GmlReader> ecitygml::GmlReader::create(diplomat::span<const uint8_t> data, ecitygml::CitygmlFormat format) {
    auto result = ecitygml::capi::ecitygml_GmlReader_new({data.data(), data.size()},
        format.AsFFI());
    return std::unique_ptr<ecitygml::GmlReader>(ecitygml::GmlReader::FromFFI(result));
}

inline diplomat::result<std::unique_ptr<ecitygml::GmlReader>, std::unique_ptr<ecitygml::Error>> ecitygml::GmlReader::from_path(std::string_view path) {
    auto result = ecitygml::capi::ecitygml_GmlReader_from_path({path.data(), path.size()});
    return result.is_ok ? diplomat::result<std::unique_ptr<ecitygml::GmlReader>, std::unique_ptr<ecitygml::Error>>(diplomat::Ok<std::unique_ptr<ecitygml::GmlReader>>(std::unique_ptr<ecitygml::GmlReader>(ecitygml::GmlReader::FromFFI(result.ok)))) : diplomat::result<std::unique_ptr<ecitygml::GmlReader>, std::unique_ptr<ecitygml::Error>>(diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline void ecitygml::GmlReader::with_rebuild_object_bounds(bool rebuild_object_bounds) {
    ecitygml::capi::ecitygml_GmlReader_with_rebuild_object_bounds(this->AsFFI(),
        rebuild_object_bounds);
}

inline diplomat::result<std::unique_ptr<ecitygml::CityModel>, std::unique_ptr<ecitygml::Error>> ecitygml::GmlReader::finish() {
    auto result = ecitygml::capi::ecitygml_GmlReader_finish(this->AsFFI());
    return result.is_ok ? diplomat::result<std::unique_ptr<ecitygml::CityModel>, std::unique_ptr<ecitygml::Error>>(diplomat::Ok<std::unique_ptr<ecitygml::CityModel>>(std::unique_ptr<ecitygml::CityModel>(ecitygml::CityModel::FromFFI(result.ok)))) : diplomat::result<std::unique_ptr<ecitygml::CityModel>, std::unique_ptr<ecitygml::Error>>(diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline const ecitygml::capi::GmlReader* ecitygml::GmlReader::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::GmlReader*>(this);
}

inline ecitygml::capi::GmlReader* ecitygml::GmlReader::AsFFI() {
    return reinterpret_cast<ecitygml::capi::GmlReader*>(this);
}

inline const ecitygml::GmlReader* ecitygml::GmlReader::FromFFI(const ecitygml::capi::GmlReader* ptr) {
    return reinterpret_cast<const ecitygml::GmlReader*>(ptr);
}

inline ecitygml::GmlReader* ecitygml::GmlReader::FromFFI(ecitygml::capi::GmlReader* ptr) {
    return reinterpret_cast<ecitygml::GmlReader*>(ptr);
}

inline void ecitygml::GmlReader::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_GmlReader_destroy(reinterpret_cast<ecitygml::capi::GmlReader*>(ptr));
}


#endif // ecitygml_GmlReader_HPP
