#ifndef ecitygml_CityModel_HPP
#define ecitygml_CityModel_HPP

#include "CityModel.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "AbstractCityObjectKindRefIterator.hpp"
#include "AbstractFeatureKindRefIterator.hpp"
#include "BoundingShape.hpp"
#include "CodeIterator.hpp"
#include "DateTime.hpp"
#include "Id.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_CityModel_id(const ecitygml::capi::CityModel* self);

    ecitygml::capi::CodeIterator* ecitygml_CityModel_names(const ecitygml::capi::CityModel* self);

    const ecitygml::capi::BoundingShape* ecitygml_CityModel_bounded_by(const ecitygml::capi::CityModel* self);

    const ecitygml::capi::Id* ecitygml_CityModel_feature_id(const ecitygml::capi::CityModel* self);

    const ecitygml::capi::DateTime* ecitygml_CityModel_creation_date(const ecitygml::capi::CityModel* self);

    const ecitygml::capi::DateTime* ecitygml_CityModel_termination_date(const ecitygml::capi::CityModel* self);

    const ecitygml::capi::DateTime* ecitygml_CityModel_valid_from(const ecitygml::capi::CityModel* self);

    const ecitygml::capi::DateTime* ecitygml_CityModel_valid_to(const ecitygml::capi::CityModel* self);

    ecitygml::capi::AbstractFeatureKindRefIterator* ecitygml_CityModel_iter_features(const ecitygml::capi::CityModel* self);

    ecitygml::capi::AbstractCityObjectKindRefIterator* ecitygml_CityModel_iter_city_objects(const ecitygml::capi::CityModel* self);

    void ecitygml_CityModel_recompute_child_bounding_shapes(ecitygml::capi::CityModel* self);

    size_t ecitygml_CityModel_city_objects_len(const ecitygml::capi::CityModel* self);

    void ecitygml_CityModel_destroy(CityModel* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::CityModel::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityModel_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::CityModel::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityModel_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::CityModel::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityModel_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::CityModel::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityModel_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::CityModel::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityModel_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::CityModel::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityModel_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::CityModel::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityModel_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::CityModel::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityModel_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractFeatureKindRefIterator> ecitygml::CityModel::iter_features() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityModel_iter_features(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractFeatureKindRefIterator>(ecitygml::AbstractFeatureKindRefIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::AbstractCityObjectKindRefIterator> ecitygml::CityModel::iter_city_objects() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityModel_iter_city_objects(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractCityObjectKindRefIterator>(ecitygml::AbstractCityObjectKindRefIterator::FromFFI(result));
}

inline void ecitygml::CityModel::recompute_child_bounding_shapes() {
    ecitygml::capi::ecitygml_CityModel_recompute_child_bounding_shapes(this->AsFFI());
}

inline size_t ecitygml::CityModel::city_objects_len() const {
    auto result = ecitygml::capi::ecitygml_CityModel_city_objects_len(this->AsFFI());
    return result;
}

inline const ecitygml::capi::CityModel* ecitygml::CityModel::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::CityModel*>(this);
}

inline ecitygml::capi::CityModel* ecitygml::CityModel::AsFFI() {
    return reinterpret_cast<ecitygml::capi::CityModel*>(this);
}

inline const ecitygml::CityModel* ecitygml::CityModel::FromFFI(const ecitygml::capi::CityModel* ptr) {
    return reinterpret_cast<const ecitygml::CityModel*>(ptr);
}

inline ecitygml::CityModel* ecitygml::CityModel::FromFFI(ecitygml::capi::CityModel* ptr) {
    return reinterpret_cast<ecitygml::CityModel*>(ptr);
}

inline void ecitygml::CityModel::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_CityModel_destroy(reinterpret_cast<ecitygml::capi::CityModel*>(ptr));
}


#endif // ecitygml_CityModel_HPP
